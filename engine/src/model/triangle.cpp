#include "model/triangle.h"
#include <GL/glut.h>

#include <tuple>

using namespace std;

namespace triangle {
    Triangle::Triangle(
            tuple<float, float, float> point1,
            tuple<float, float, float> point2,
            tuple<float, float, float> point3
    ) {
        p1 = make_tuple(get<0>(point1), get<1>(point1), get<2>(point1));
        p2 = make_tuple(get<0>(point2), get<1>(point2), get<2>(point3));
        p3 = make_tuple(get<0>(point3), get<1>(point3), get<2>(point3));
    }

    Triangle::Triangle(
            float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3
    ) {
        p1 = make_tuple(x1, y1, z1);
        p2 = make_tuple(x2, y2, z2);
        p3 = make_tuple(x3, y3, z3);
    }

    tuple<float, float, float> Triangle::get_p1() {
        return p1;
    }

    tuple<float, float, float> Triangle::get_p2() {
        return p2;
    }

    tuple<float, float, float> Triangle::get_p3() {
        return p3;
    }
}
