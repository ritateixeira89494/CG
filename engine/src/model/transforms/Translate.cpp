#include "model/transforms/Translate.h"
#include "model/transforms/Transform.h"
#include "utils/matrix.h"
#include "GL/glut.h"

#include <vector>
#include <tuple>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

Translate::Translate(float x, float y, float z) : Transform(x, y, z) {
    dynamic = false;
    full_time = seconds{0};
    start = -1;
    align = false;
    ctrl_points = {};
    draw = false;
}

Translate::Translate(int time, bool alignment, bool d, int segments, vector<tuple<float,float,float>> points) : Transform(0,0,0) {
    dynamic        = true;
    full_time      = milliseconds{time*1000};
    start          = -1;
    align          = alignment;
    ctrl_points    = points;
    draw           = d;
    curve_segments = segments;
}

Translate::Translate(int time, bool alignment, bool d, int segments) : Transform(0,0,0) {
    dynamic        = true;
    full_time      = milliseconds{time*1000};
    start          = -1;
    align          = alignment;
    ctrl_points    = {};
    draw           = d;
    curve_segments = segments;
}

void Translate::get_catmull_rom_point(float t, tuple<float,float,float> p0, tuple<float,float,float> p1, tuple<float,float,float> p2, tuple<float,float,float> p3, float *pos, float *deriv) {
    float catmull_rom_matrix[4][4] = {
        {-0.5f,  1.5f, -1.5f,  0.5f},
		{ 1.0f, -2.5f,  2.0f, -0.5f},
		{-0.5f,  0.0f,  0.5f,  0.0f},
		{ 0.0f,  1.0f,  0.0f,  0.0f}
    };

    float p0_arr[3] = { get<0>(p0), get<1>(p0), get<2>(p0) };
    float p1_arr[3] = { get<0>(p1), get<1>(p1), get<2>(p1) };
    float p2_arr[3] = { get<0>(p2), get<1>(p2), get<2>(p2) };
    float p3_arr[3] = { get<0>(p3), get<1>(p3), get<2>(p3) };

    float A[4][4];
    float T[4] = { t*t*t, t*t, t, 1 };
    float Tderiv[4] = { 3*t*t, 2*t, 1, 0 };

    for(int i = 0; i < 3; i++) {
        float v[4] = { p0_arr[i], p1_arr[i], p2_arr[i], p3_arr[i] };
        mult_matrix_vector((float *) catmull_rom_matrix, v, A[i]);

        pos[i] = T[0]*A[i][0] + T[1]*A[i][1] + T[2]*A[i][2] + T[3]*A[i][3];

        deriv[i] = Tderiv[0]*A[i][0] + Tderiv[1]*A[i][1] + Tderiv[2]*A[i][2] + Tderiv[3]*A[i][3];
    }
}

void Translate::get_global_catmull_rom_point(float gt, float *pos, float *deriv) {
    int n_points = ctrl_points.size();

    float t = gt * n_points;
    int index = floor(t);
    t = t - index;

    int indices[4];
    indices[0] = (index + n_points-1) % n_points;
    indices[1] = (indices[0]+1) % n_points;
    indices[2] = (indices[1]+1) % n_points;
    indices[3] = (indices[2]+1) % n_points;

    auto p0 = ctrl_points[indices[0]];
    auto p1 = ctrl_points[indices[1]];
    auto p2 = ctrl_points[indices[2]];
    auto p3 = ctrl_points[indices[3]];

    get_catmull_rom_point(t, p0, p1, p2, p3, pos, deriv);
}

void Translate::draw_curve() {
    if(!dynamic || !draw) { // Check if this is a static translate or if the draw flag is disabled
        return;
    }

    float pos[4];
    float deriv[4];

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < curve_segments; i++) {
        float t = (i*1.0f) / curve_segments;
        get_global_catmull_rom_point(t, pos, deriv);
        glVertex3f(pos[0],pos[1],pos[2]);
    }
    glEnd();
}

void Translate::apply() {
    if(!dynamic) {
        glTranslatef(this->x, this->y, this->z);
    } else {
        if(start == -1) {
            start = glutGet(GLUT_ELAPSED_TIME);
        }
        int now = glutGet(GLUT_ELAPSED_TIME);
        
        float pos[4];
        float deriv[4];

        float gt = (now-start)*1.0f / full_time.count();       

        get_global_catmull_rom_point(gt, pos, deriv);

        glTranslatef(pos[0], pos[1], pos[2]);

        if(align) {
            float z[3];
            float y[3];

            cross(deriv, last_y, z);
            cross(z, deriv, y);

            normalize(deriv);
            normalize(y);
            normalize(z);

            last_y[0] = y[0];
            last_y[1] = y[1];
            last_y[2] = y[2];

            float rotation[4][4] = {
                {deriv[0], deriv[1], deriv[2], 0},
                {y[0], y[1], y[2], 0},
                {z[0], z[1], z[2], 0},
                {0, 0, 0, 1}
            };

            glMultMatrixf((float *) rotation);
        }
    }
}

void Translate::set_dynamic(bool d) {
    this->dynamic = d;
}
bool Translate::get_dynamic() {
    return dynamic;
}

void Translate::set_full_time(int time) {
    this->full_time = milliseconds{time};
}
int Translate::get_full_time() {
    return full_time.count();
}

void Translate::set_start(int start) {
    this->start = start;
}
int Translate::get_start() {
    return start;
}

void Translate::set_align(bool alignment) {
    this->align = alignment;
}
bool Translate::get_align() {
    return align;
}

void Translate::set_ctrl_points(vector<tuple<float,float,float>> points) {
    this->ctrl_points = points;
}

vector<tuple<float,float,float>> Translate::get_ctrl_points() {
    return ctrl_points;
}

void Translate::set_draw(bool draw) {
    this->draw = draw;
}
bool Translate::get_draw() {
    return draw;
}