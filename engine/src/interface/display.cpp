#include <GL/glut.h>

#include "display.h"
#include "scene.h"

using namespace interface;

Scene *scene;

void placeAxis() {
        glBegin(GL_LINES);
        // X axis in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f( 10.0f, 0.0f, 0.0f);
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
    if(h == 0)
        h = 1;
    
    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45, ratio, 1, 1000);
    
    glMatrixMode(GL_MODELVIEW);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(
        15, 15, 10,
        0,  0,  0,
        0,  1,  0
    );

    placeAxis();
    scene->render_models();

    glutSwapBuffers();
}

void run(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG2022 Engine");

    scene = new Scene(argv[1]);

    glutDisplayFunc(render);
    glutReshapeFunc(change_size);

    glEnable(GL_DEPTH_TEST);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glutMainLoop();
}