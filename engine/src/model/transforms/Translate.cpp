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
    curr_time = milliseconds{0};
    start_clock = system_clock::time_point::min();
    align = false;
    ctrl_points = {};
    draw = false;
}

Translate::Translate(int time, bool alignment, bool d, int segments, vector<float *> points) : Transform(0,0,0) {
    dynamic = true;
    full_time   = seconds{time};
    curr_time   = milliseconds{0};
    start_clock = system_clock::time_point::min();
    align       = alignment;
    ctrl_points = points;
    draw = d;
    curve_segments = segments;
}

Translate::Translate(int time, bool alignment, bool d, int segments) : Transform(0,0,0) {
    dynamic = true;
    full_time   = seconds{time};
    curr_time   = milliseconds{0};
    start_clock = system_clock::time_point::min();
    align       = alignment;
    ctrl_points = {};
    draw = d;
    curve_segments = segments;
}

void Translate::get_catmull_rom_point(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {
    float catmull_rom_matrix[4][4] = {
        {-0.5f,  1.5f, -1.5f,  0.5f},
		{ 1.0f, -2.5f,  2.0f, -0.5f},
		{-0.5f,  0.0f,  0.5f,  0.0f},
		{ 0.0f,  1.0f,  0.0f,  0.0f}
    };

    float A[4][4];

    float T[4] = { t*t*t, t*t, t, 1 };
    float Tderiv[4] = { 3*t*t, 2*t, 1, 0 };

    for(int i = 0; i < 3; i++) {
        float v[4] = { p0[i], p1[i], p2[i], p3[i] };
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

    get_catmull_rom_point(t, ctrl_points[indices[0]], ctrl_points[indices[1]], ctrl_points[indices[2]], ctrl_points[indices[3]], pos, deriv);
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
        if(start_clock == system_clock::time_point::min()) {
            start_clock = system_clock::now();
        }
        auto new_clock = system_clock::now();
        curr_time = duration_cast<milliseconds>(new_clock - start_clock);
        
        float pos[4];
        float deriv[4];

        float gt = (curr_time.count() / (full_time.count()*1000.0f));       

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

        if(curr_time > full_time) {
            curr_time -= full_time;
        }
    }
}

void Translate::set_dynamic(bool d) {
    dynamic = d;
}
bool Translate::get_dynamic() {
    return dynamic;
}
