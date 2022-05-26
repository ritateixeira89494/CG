#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#endif

#include "model/transforms/Transform.h"
#include "model/transforms/Translate.h"
#include "interface/display.h"
#include "interface/scene.h"
#include "interface/view.h"
#include "interface/perspective.h"
#include "utils/coords.h"
#include "utils/misc.h"
#include <cmath>
#include <iostream>

using namespace interface;

Scene scene;

GLuint modes[3] = {GL_FILL, GL_LINE,  GL_POINT};
int mode = 0; // Specifies the current active mode in the modes array

bool cam_mode = false;
bool axis = true;
bool sel_mode = false;

int width = 800;
int height = 800;

string file_path;

int dclick = 0;

int multiview = 1;

// Normal perspective that the user can move.
// It is initialized like this because the compiler complains if we don't initialize it.
// This value is never used and is replaced right after the scene is loaded.
Perspective normal = Perspective(1, 1, 1);

// List of perspectives
vector<Perspective *> perspectives = {
        &normal
};

View *view = new View;
View selected;

void placeAxis() {
    glBegin(GL_LINES);
    // X Axis in red
    float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, red);
    glVertex3f(-1000.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
    // Y Axis in Green
    float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, green);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, green);
    glVertex3f(0.0f, -1000.0f, 0.0f);
    glVertex3f(0.0f, 1000.0f, 0.0f);
    // Z Axis in Blue
    float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blue);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blue);
    glVertex3f(0.0f, 0.0f, -1000.0f);
    glVertex3f(0.0f, 0.0f, 1000.0f);
    glEnd();
}

void change_size(int w, int h) {
    if (h == 0)
        h = 1;

    width = w;
    height = h;
}

void update_perspectives_rec(vector<Perspective *> ps, View **v) {
    auto split = split_vector<Perspective *>(ps);
    vector<Perspective *> first = get<0>(split);
    vector<Perspective *> second = get<1>(split);

    if (*v == nullptr) {
        *v = new View();
    } else {
        (*v)->set_perspective(nullptr);
    }

    if (first.size() == 1) {
        if (second.empty()) {
            *v = new View(first[0]);
        } else {
            View *left = new View(first[0]);
            View *right = new View(second[0]);

            (*v)->set_perspective(nullptr);
            (*v)->set_left(left);
            (*v)->set_right(right);
            (*v)->set_div(0.50);
        }
    } else {
        update_perspectives_rec(first, (*v)->get_left());
        if (second.size() != 1) {
            update_perspectives_rec(second, (*v)->get_right());
        } else {
            View *r = new View(second[0]);
            (*v)->set_right(r);
        }
    }
}

void update_perspectives() {
    vector<Perspective *> ps(perspectives.begin(), perspectives.begin() + multiview);
    update_perspectives_rec(ps, &view);
}

void render_normal() {
    scene.place_lights();

    if (axis)
        placeAxis();

    auto m_rotation_alpha = scene.get_model_rotation_alpha();
    auto m_rotation_beta = scene.get_model_rotation_beta();

    auto position = scene.get_position();

    if (cam_mode)
        glColor3f(0.36, 0.8, 0.89); // #5CCCE2
    else
        glColor3f(1, 1, 1); // #FFFFFF

    // Default changeable transforms
    auto scale = scene.get_scale();
    glTranslatef(get<0>(position), get<1>(position), get<2>(position));
    glRotatef(radian2degree(m_rotation_alpha), 0, 1, 0);
    glRotatef(radian2degree(m_rotation_beta), 0, 0, 1);
    glScalef(scale, scale, scale);
    scene.render_models(cam_mode);
    glScalef(1 / scale, 1 / scale, 1 / scale);
    glTranslatef(-get<0>(position), -get<1>(position), -get<2>(position));

}

void render_rec(View v, int start_x, int start_y, int w, int h, bool horizontal) {
    if (v.get_perpective() == nullptr) {
        int new_w = w;
        int new_h = h;
        if (horizontal) {
            new_w = floor(w * v.get_div());
            render_rec(**v.get_left(), start_x, start_y, new_w, new_h, !horizontal);
            render_rec(**v.get_right(), start_x + new_w, start_y, w - new_w, new_h, !horizontal);
        } else {
            new_h = floor(h * v.get_div());
            render_rec(**v.get_left(), start_x, start_y, new_w, new_h, !horizontal);
            render_rec(**v.get_right(), start_x, start_y + new_h, new_w, h - new_h, !horizontal);
        }
    } else {
        // Set black background for the view, but a little smaller
        // so that we get a white border
        glEnable(GL_SCISSOR_TEST);
        glScissor(start_x + 1, start_y + 1, w - 2, h - 2);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);

        // Get the view's aspect ratio
        float ratio = (w - 2.0f) / (h - 2.0f);
        // Set the perspective, to keep the proper aspect ratio
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(scene.get_fov(), ratio, scene.get_near(), scene.get_far());
        glMatrixMode(GL_MODELVIEW);

        glViewport(start_x + 1, start_y + 1, w - 2,
                   h - 2); // Set the viewport to the same size we set for the black background
        glLoadIdentity();

        // Set the camera according to the perspective
        Perspective p = *v.get_perpective();
        auto cam_pos = p.get_cam_pos();
        auto cam_center = p.get_cam_center();
        auto up = p.get_up();
        gluLookAt(
                get<0>(cam_pos), get<1>(cam_pos), get<2>(cam_pos),
                get<0>(cam_center), get<1>(cam_center), get<2>(cam_center),
                get<0>(up), get<1>(up), get<2>(up)
        );
        render_normal(); // Render the scene
    }
}

void render() {
    glClearColor(1, 1, 1, 1); // Set a white background in the entire window
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT); // Clear the bit buffer and the color buffer with the color set above

    View *v;
    // Render views
    if (sel_mode) {
        v = &selected;
    } else {
        v = view;
    }
    render_rec(*v, 0, 0, width, height, true);

    // Display buffer
    glutSwapBuffers();
}

Perspective *get_selected_perspective(View *v, int start_x, int start_y, int w, int h, bool horizontal, int x, int y) {
    int division_point;

    if (v->get_perpective() == nullptr) {
        if (horizontal) {
            int new_w = w * v->get_div();
            division_point = start_x + new_w;

            if (x < division_point) {
                return get_selected_perspective(*v->get_left(), start_x, start_y, new_w, h, !horizontal, x, y);
            } else {
                return get_selected_perspective(*v->get_right(), start_x + new_w, start_y, new_w, h, !horizontal, x, y);
            }
        } else {
            int new_h = h * v->get_div();
            division_point = start_y + new_h;

            if (y < division_point) {
                return get_selected_perspective(*v->get_left(), start_x, start_y, w, new_h, !horizontal, x, y);
            } else {
                return get_selected_perspective(*v->get_right(), start_x, start_y + new_h, w, new_h, !horizontal, x, y);
            }
        }
    } else {
        return v->get_perpective();
    }
}

View *get_selected_view(View *v, int *start_x, int *start_y, int *w, int *h, bool *horizontal, int x, int y) {
    if (v->get_perpective() == nullptr) {
        if (*horizontal) {
            float new_w = (*w) * v->get_div();
            int division_point = *start_x + new_w;

            if (
                    division_point - 10 < x && x < division_point + 10
                    && *start_y < y && y < *start_y + *h
                    ) {
                return v;
            } else if (x < division_point) {
                *horizontal = !(*horizontal);
                *w = new_w;
                return get_selected_view(*v->get_left(), start_x, start_y, w, h, horizontal, x, y);
            } else {
                *horizontal = !(*horizontal);
                *start_x = *start_x + new_w;
                *w = *w - new_w;
                return get_selected_view(*v->get_right(), start_x, start_y, w, h, horizontal, x, y);
            }
        } else {
            float new_h = (*h) * v->get_div();
            int division_point = *start_y + new_h;

            if (
                    division_point - 3 < y && y < division_point + 3
                    && *start_x < x && x < *start_x + (*w)
                    ) {
                return v;
            } else if (y < division_point) {
                *horizontal = !(*horizontal);
                *h = new_h;
                return get_selected_view(*v->get_left(), start_x, start_y, w, h, horizontal, x, y);
            } else {
                *horizontal = !(*horizontal);
                *start_y = *start_y + new_h;
                *h = *h - new_h;
                return get_selected_view(*v->get_right(), start_x, start_y, w, h, horizontal, x, y);
            }
        }
    } else {
        return nullptr;
    }
}

void parse_spec_key(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (cam_mode)
                normal = scene.rotate_camera(-0.1, 0);
            else
                scene.rotate_models(-0.1, 0);
            break;
        case GLUT_KEY_RIGHT:
            if (cam_mode)
                normal = scene.rotate_camera(0.1, 0);
            else
                scene.rotate_models(0.1, 0);
            break;
        case GLUT_KEY_UP:
            if (cam_mode)
                normal = scene.rotate_camera(0, -0.1);
            else
                scene.rotate_models(0, -0.1);
            break;
        case GLUT_KEY_DOWN:
            if (cam_mode)
                normal = scene.rotate_camera(0, 0.1);
            else
                scene.rotate_models(0, 0.1);
            break;
        default:
            return;
    }
    glutPostRedisplay();
}

void parse_key(unsigned char key, int x, int y) {
    switch (key) {
        // Switch between fill mode and line mode
        case 'P':
        case 'p':
            if (mode == 2)
                mode = 0;
            else mode++;

            glPolygonMode(GL_FRONT, modes[mode]);
            break;
        case 'A':
        case 'a':
            if (cam_mode)
                normal = scene.move_camera(-M_PI / 2);
            else
                scene.move_models(-M_PI / 2);
            break;
        case 'D':
        case 'd':
            if (cam_mode)
                normal = scene.move_camera(M_PI / 2);
            else
                scene.move_models(M_PI / 2);
            break;
        case 'W':
        case 'w':
            if (cam_mode)
                normal = scene.move_camera(M_PI);
            else
                scene.move_models(M_PI);
            break;
        case 'S':
        case 's':
            if (cam_mode)
                normal = scene.move_camera(0);
            else
                scene.move_models(0);
            break;
        case '+':
            if (cam_mode)
                normal = scene.zoom(-0.2);
            else
                scene.change_scale(0.1);
            break;
        case '-':
            if (cam_mode)
                normal = scene.zoom(0.2);
            else
                scene.change_scale(-0.1);
            break;
        case '\r':
            cam_mode = !cam_mode;
            break;
        case 'V':
        case 'v':
            multiview = !multiview;
            break;
        case 'E':
        case 'e':
            axis = !axis;
            break;
        case 'R':
        case 'r':
            scene = Scene(file_path.data());
            break;
        case 'Q':
        case 'q':
            std::cout << "Goodbye!!" << std::endl;
            exit(0);
        case '1':
            if (!sel_mode) {
                multiview = 1;
                update_perspectives();
            }
            break;
        case '2':
            if (!sel_mode) {
                multiview = 2;
                update_perspectives();
            }
            break;
        case '3':
            if (!sel_mode) {
                multiview = 3;
                update_perspectives();
            }
            break;
        case '4':
            if (!sel_mode) {
                multiview = 4;
                update_perspectives();
            }
            break;
        case '5':
            if (!sel_mode) {
                multiview = 5;
                update_perspectives();
            }
            break;
        case '6':
            if (!sel_mode) {
                multiview = 6;
                update_perspectives();
            }
            break;
        case '7':
            if (!sel_mode) {
                multiview = 7;
                update_perspectives();
            }
            break;
        default:
            return;
    }

    glutPostRedisplay();
}

int ticket = 0;

void reset_dclick(int x) {
    if (x == ticket)
        dclick = 0;
}

// TODO: Improve code quality

int start_x, start_y;
bool tracking = false;
View *ve;
bool horizontal = true;
int w = width;
int h = height;

void onMouseClick(int key, int state, int x, int y) {
    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN && multiview != 1) {
        dclick++;
        if (dclick == 1) {
            glutTimerFunc(1000, reset_dclick, ticket++);
        } else if (dclick == 2) {
            sel_mode = !sel_mode;
            if (sel_mode) {
                Perspective *sel = get_selected_perspective(view, 0, 0, width, height, true, x, height - y);
                selected.set_perspective(sel);
            }
            dclick = 0;
        }
    } else if (key == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            horizontal = true;
            w = width;
            h = height;
            start_x = 0;
            start_y = 0;
            ve = get_selected_view(view, &start_x, &start_y, &w, &h, &horizontal, x, height - y);
            if (ve != nullptr)
                tracking = true;
        } else if (state == GLUT_UP) {
            tracking = false;
        }

    }
    glutPostRedisplay();
}

void on_mouse_motion(int x, int y) {
    int delta_x, delta_y;
    if (!tracking)
        return;

    float lol = (float) (x - start_x) / (float) w;
    float yay = (float) (height - y - start_y) / (float) h;

    if (tracking) {
        float new_div;
        if (horizontal) {
            new_div = lol;
        } else {
            new_div = yay;
        }
        ve->set_div(new_div);
    }
    glutPostRedisplay();
}

void set_gl_settings(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("CG2022 Engine");

    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutReshapeFunc(change_size);
    glutKeyboardFunc(parse_key);
    glutSpecialFunc(parse_spec_key);
    glutMouseFunc(onMouseClick);
    glutMotionFunc(on_mouse_motion);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glPolygonMode(GL_FRONT, modes[mode]);

    glewInit();
}

void run(int argc, char *argv[]) {
    set_gl_settings(argc, argv);

    file_path.assign(argv[1]);
    scene = Scene(argv[1]);

    normal = scene.get_perspective();
    auto per = normal.get_cam_pos();

    perspectives.emplace_back(new Perspective(get<0>(per) * 2, 0, 0));
    perspectives.emplace_back(new Perspective(0, get<1>(per) * 2, 0.01));
    perspectives.emplace_back(new Perspective(0, 0, get<2>(per) * 2));
    perspectives.emplace_back(new Perspective(-(get<0>(per) * 2), 0, 0));
    perspectives.emplace_back(new Perspective(0, -(get<1>(per) * 2), 0.01));
    perspectives.emplace_back(new Perspective(0, 0, -(get<2>(per) * 2)));

    update_perspectives();

    glutMainLoop();
}
