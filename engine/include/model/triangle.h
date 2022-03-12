#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <GL/gl.h>
#include <GL/glut.h>

#include <tuple>

using namespace std;

namespace triangle {
    class Triangle {
    private:
        tuple<GLfloat, GLfloat, GLfloat> p1;
        tuple<GLfloat, GLfloat, GLfloat> p2;
        tuple<GLfloat, GLfloat, GLfloat> p3;
    public:
        Triangle();

        Triangle(tuple<GLfloat, GLfloat, GLfloat> p1, tuple<GLfloat, GLfloat, GLfloat> p2,
                 tuple<GLfloat, GLfloat, GLfloat> p3);

        Triangle(
                GLfloat x1, GLfloat y1, GLfloat z1,
                GLfloat x2, GLfloat y2, GLfloat z2,
                GLfloat x3, GLfloat y3, GLfloat z3
        );

        tuple<GLfloat, GLfloat, GLfloat> get_p1();

        tuple<GLfloat, GLfloat, GLfloat> get_p2();

        tuple<GLfloat, GLfloat, GLfloat> get_p3();
    };
}

#endif // __TRIANGLE_H__
