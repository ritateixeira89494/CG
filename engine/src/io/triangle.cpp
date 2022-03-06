#include "triangle.h"
#include <GL/gl.h>
#include <type_traits>

#include <tuple>

using namespace std;

namespace triangle {
    Triangle::Triangle() {
        p1 = make_tuple(0, 0, 0);
        p2 = make_tuple(0, 0, 0);
        p3 = make_tuple(0, 0, 0);
    }

    Triangle::Triangle(tuple<GLfloat, GLfloat, GLfloat> point1, tuple<GLfloat, GLfloat, GLfloat> point2, tuple<GLfloat, GLfloat, GLfloat> point3) {
        p1 = make_tuple(get<0>(point1), get<1>(point1), get<2>(point1));
        p2 = make_tuple(get<0>(point2), get<1>(point2), get<2>(point3));
        p3 = make_tuple(get<0>(point3), get<1>(point3), get<2>(point3));
    }

    Triangle::Triangle(
            GLfloat x1, GLfloat y1, GLfloat z1,
            GLfloat x2, GLfloat y2, GLfloat z2,
            GLfloat x3, GLfloat y3, GLfloat z3
    ) {
        p1 = make_tuple(x1, y1, z1);
        p2 = make_tuple(x2, y2, z2);
        p3 = make_tuple(x3, y3, z3);
    }

    tuple<GLfloat, GLfloat, GLfloat> Triangle::get_p1() {
        return p1;
    }

    tuple<GLfloat, GLfloat, GLfloat> Triangle::get_p2() {
        return p2;
    }

    tuple<GLfloat, GLfloat, GLfloat> Triangle::get_p3() {
        return p3;
    }
}
