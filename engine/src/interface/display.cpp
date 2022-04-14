#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include "model/transforms/Transform.h"
#include "model/transforms/Translate.h"
#include <iostream>
#include "interface/display.h"
#include "interface/scene.h"
#include "interface/view.h"
#include "interface/perspective.h"
#include "utils/coords.h"
#include "utils/misc.h"
#include <math.h>

using namespace interface;

Scene scene;

bool model_mode = true;
bool axis = true;
int multiview = 1;
bool sel_mode = false;

int width = 800;
int height = 800;

// Normal perspective that the user can move.
// It is initialized like this because the compiler complains if we don't initialize it.
// This value is never used and is replaced right after the scene is loaded.
Perspective normal = Perspective(1,1,1);

vector<Perspective *> perspectives = {
        &normal,
        new Perspective(10, 0, 0),
        new Perspective(0, 10, 0.01),
        new Perspective(0,0,10)
};

View *view = new View;

View selected;

void placeAxis() {
    glBegin(GL_LINES);
    // X Axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
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

    if(*v == nullptr) {
        *v = new View();
    } else {
        (*v)->set_perspective(nullptr);
    }

    if(first.size() == 1){
        if(second.size() == 0) {
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
        if(second.size() != 1) {
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
    if (axis)
        placeAxis();

    auto m_rotation_alpha = scene.get_model_rotation_alpha();
    auto m_rotation_beta = scene.get_model_rotation_beta();

    auto position = scene.get_position();

    if (model_mode)
        glColor3f(1, 1, 1); // #FFFFFF
    else
        glColor3f(0.36, 0.8, 0.89); // #5CCCE2

    // Default changeable transforms
    auto scale = scene.get_scale();
    glTranslatef(get<0>(position), get<1>(position), get<2>(position));
    glRotatef(radian2degree(m_rotation_alpha), 0, 1, 0);
    glRotatef(radian2degree(m_rotation_beta), 0, 0, 1);
    glScalef(scale, scale, scale);
    scene.render_models();
    glScalef(1/scale,1/scale,1/scale);
    glTranslatef(-get<0>(position), -get<1>(position), -get<2>(position));

}

void render_rec(View v, int start_x, int start_y, int w, int h, bool horizontal) {
    if(v.get_perpective() == nullptr) {
        int new_w = w;
        int new_h = h;
        if (horizontal) {
            new_w = floor(w * v.get_div());
            render_rec(**v.get_left(), start_x, start_y, new_w, new_h, !horizontal);
            render_rec(**v.get_right(), start_x + new_w, start_y, w-new_w, new_h, !horizontal);
        } else {
            new_h = floor(h * v.get_div());
            render_rec(**v.get_left(), start_x, start_y, new_w, new_h, !horizontal);
            render_rec(**v.get_right(), start_x, start_y + new_h, new_w, h-new_h, !horizontal);
        }
    } else {
        // Set black background for the view, but a little smaller
        // so that we get a white border
        glEnable(GL_SCISSOR_TEST);
            glScissor(start_x+1,start_y+1,w-2,h-2);
            glClearColor(0,0,0,1);
            glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);

        // Get the view's aspect ratio
        float ratio = (w-2.0f) / (h-2.0f);
        // Set the perspective, to keep the proper aspect ratio
        glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(scene.get_fov(), ratio, scene.get_near(), scene.get_far());
        glMatrixMode(GL_MODELVIEW);

        glViewport(start_x+1, start_y+1, w-2, h-2); // Set the viewport to the same size we set for the black background
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
    glClearColor(1,1,1,1); // Set a white background in the entire window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the bit buffer and the color buffer with the color set above

    View *v;
    // Render views
    if(sel_mode) {
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

    if(v->get_perpective() == nullptr) {
        if(horizontal) {
            int new_w = w*v->get_div();
            division_point = start_x + new_w;

            if(x < division_point) {
                return get_selected_perspective(*v->get_left(), start_x, start_y, new_w, h, !horizontal, x, y);
            } else {
                return get_selected_perspective(*v->get_right(), start_x + new_w, start_y, new_w, h, !horizontal, x, y);
            }
        } else {
            int new_h = h*v->get_div();
            division_point = start_y + new_h;

            if(y < division_point) {
                return get_selected_perspective(*v->get_left(), start_x, start_y, w, new_h, !horizontal, x, y);
            } else {
                return get_selected_perspective(*v->get_right(), start_x, start_y + new_h, w, new_h, !horizontal, x, y);
            }
        }
    } else {
        return v->get_perpective();
    }
}

void parse_spec_key(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (model_mode)
                scene.rotate_models(-0.1, 0);
            else
                normal = scene.rotate_camera(-0.1, 0);
            break;
        case GLUT_KEY_RIGHT:
            if (model_mode)
                scene.rotate_models(0.1, 0);
            else
                normal = scene.rotate_camera(0.1, 0);
            break;
        case GLUT_KEY_UP:
            if (model_mode)
                scene.rotate_models(0, -0.1);
            else
                normal = scene.rotate_camera(0, -0.1);
            break;
        case GLUT_KEY_DOWN:
            if (model_mode)
                scene.rotate_models(0, 0.1);
            else
                normal = scene.rotate_camera(0, 0.1);
            break;
        default:
            return;
    }
    glutPostRedisplay();
}

void parse_key(unsigned char key, int x, int y) {
    switch (key) {
        case 'A':
        case 'a':
            if (model_mode)
                scene.move_models(-M_PI/2);
            else
                normal = scene.move_camera(-M_PI/2);
            break;
        case 'D':
        case 'd':
            if (model_mode)
                scene.move_models(M_PI/2);
            else
                normal = scene.move_camera(M_PI/2);
            break;
        case 'W':
        case 'w':
            if (model_mode)
                scene.move_models(M_PI);
            else
                normal = scene.move_camera(M_PI);
            break;
        case 'S':
        case 's':
            if (model_mode)
                scene.move_models(0);
            else
                normal = scene.move_camera(0);
            break;
        case '+':
            if (model_mode)
                scene.change_scale(0.1);
            else
                normal = scene.zoom(-0.1);
            break;
        case '-':
            if (model_mode)
                scene.change_scale(-0.1);
            else
                normal = scene.zoom(0.1);
            break;
        case '\r':
            model_mode = !model_mode;
            break;
        case 'V':
        case 'v':
            multiview = !multiview;
            break;
        case 'E':
        case 'e':
            axis = !axis;
            break;
        case 'Q':
        case 'q':
            std::cout << "Goodbye!!" << std::endl;
            exit(0);
        case '1':
            if(!sel_mode) {
                multiview = 1;
                update_perspectives();
            }
            break;
        case '2':
            if(!sel_mode) {
                multiview = 2;
                update_perspectives();
            }
            break;
        case '3':
            if(!sel_mode) {
                multiview = 3;
                update_perspectives();
            }
            break;
        case '4':
            if(!sel_mode) {
                multiview = 4;
                update_perspectives();
            }
            break;
        default:
            return;
    }

    glutPostRedisplay();
}

void onMouseClick(int key, int state, int x, int y) {
    if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN && multiview != 1) {
        sel_mode = !sel_mode;
        if(sel_mode) {
            Perspective *sel = get_selected_perspective(view, 0, 0, width, height, true, x, height-y);
            selected.set_perspective(sel);
        }
    }
    glutPostRedisplay();
}

void run(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("CG2022 Engine");

    glutDisplayFunc(render);
    glutReshapeFunc(change_size);
    glutKeyboardFunc(parse_key);
    glutSpecialFunc(parse_spec_key);
    glutMouseFunc(onMouseClick);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_LINE);

    scene = Scene(argv[1]);

    normal = scene.get_perspective();
    update_perspectives();

    glutMainLoop();
}