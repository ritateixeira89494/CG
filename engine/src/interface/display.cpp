#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "interface/display.h"
#include "interface/scene.h"
#include "utils/coords.h"

using namespace interface;

Scene *scene;

bool model_mode = true;

void placeAxis() {
    glBegin(GL_LINES);
    // X Axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
}

void change_size(int w, int h) {
    if (h == 0)
        h = 1;

    float ratio = w * 1.0f / h;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(scene->get_fov(), ratio, scene->get_near(), scene->get_far());

    glMatrixMode(GL_MODELVIEW);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    tuple<GLfloat, GLfloat, GLfloat> cam_pos = scene->get_camera_pos();
    tuple<GLfloat, GLfloat, GLfloat> cam_center = scene->get_camera_center();
    tuple<GLfloat, GLfloat, GLfloat> up = scene->get_up();

    gluLookAt(
            get<0>(cam_pos), get<1>(cam_pos), get<2>(cam_pos),
            get<0>(cam_center), get<1>(cam_center), get<2>(cam_center),
            get<0>(up), get<1>(up), get<2>(up)
    );

    placeAxis();

    auto m_rotation_alpha = scene->get_model_rotation_alpha();
    auto m_rotation_beta = scene->get_model_rotation_beta();

    auto position = scene->get_position();

    if(model_mode)
        glColor3f(1,1,1);
    else
        glColor3f(0.36,0.8,0.89); // #5CCCE2
    
    auto scale = scene->get_scale();
    glTranslatef(get<0>(position), get<1>(position), get<2>(position));
    glRotatef(radian2degree(m_rotation_alpha), 0, 1, 0);
    glRotatef(radian2degree(m_rotation_beta), 1, 0, 0);
    glTranslatef(-get<0>(position), -get<1>(position), -get<2>(position));

    scene->render_models();

    glutSwapBuffers();
}

void parse_spec_key(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT:
            if(model_mode)
                scene->rotate_models(-0.1, 0);
            else
                scene->rotate_camera(-0.1, 0);
            break;
        case GLUT_KEY_RIGHT:
            if(model_mode)
                scene->rotate_models(0.1, 0);
            else
                scene->rotate_camera(0.1, 0);
            break;
        case GLUT_KEY_UP:
            if(model_mode)
                scene->rotate_models(0, -0.1);
            else
                scene->rotate_camera(0, -0.1);
            break;
        case GLUT_KEY_DOWN:
            if(model_mode)
                scene->rotate_models(0, 0.1);
            else
                scene->rotate_camera(0, 0.1);
            break;
        default:
            return;
    }
    glutPostRedisplay();
}

void parse_key(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            if(model_mode)
                scene->move_models(-0.1, 0, 0);
            else
                scene->move_camera(-0.1, 0, 0);
            break;
        case 'd':
            if(model_mode)
                scene->move_models(0.1, 0, 0);
            else
                scene->move_camera(0.1, 0, 0);
            break;
        case 'w':
            if(model_mode)
                scene->move_models(0, 0, -0.1);
            else
                scene->move_camera(0, 0, -0.1);
            break;
        case 's':
            if(model_mode)
                scene->move_models(0, 0, 0.1);
            else
                scene->move_camera(0, 0, 0.1);
            break;
        case '+':
            if(model_mode)
                scene->change_scale(0.1);
            else
                scene->zoom(-0.1);
            break;
        case '-':
            if(model_mode)
                scene->change_scale(-0.1);
            else
                scene->zoom(0.1);
            break;
        case '\r':
            model_mode = !model_mode;
            break;
        case 'q':
            std::cout << "Goodbye!!" << std::endl;
            exit(0);
            break;
        default:
            return;
    }

    glutPostRedisplay();
}

void run(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG2022 Engine");

    glutDisplayFunc(render);
    glutReshapeFunc(change_size);
    glutKeyboardFunc(parse_key);
    glutSpecialFunc(parse_spec_key);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_LINE);

    scene = new Scene(argv[1]);

    glutMainLoop();
}