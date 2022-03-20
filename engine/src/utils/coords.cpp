#include <tuple>
#include <cmath>
#include "utils/coords.h"

using namespace std;

float radian2degree(float angle) {
    return angle * 180 / M_PI;
}

tuple<float, float, float> spherical2cartesian(float radius, float alpha, float beta) {
    float x = radius * sin(beta) * sin(alpha);
    float y = radius * cos(beta);
    float z = radius * sin(beta) * cos(alpha);

    return make_tuple(x, y, z);
}

tuple<float, float, float> cartesian2spherical(float x, float y, float z) {
    float radius = sqrt(x * x + y * y + z * z);
    float alpha = atan(x / z);
    float beta = acos(y / radius);

    return make_tuple(radius, alpha, beta);
}