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

}

Translate::Translate(int time, bool alignment, vector<float *> points) : Transform(0,0,0) {
    dynamic = true;
    full_time   = seconds{time};
    curr_time   = milliseconds{0};
    start_clock = system_clock::time_point::min();
    align       = alignment;
    ctrl_points = points;
}

Translate::Translate(int time, bool alignment) : Transform(0,0,0) {
    dynamic = true;
    full_time   = seconds{time};
    curr_time   = milliseconds{0};
    start_clock = system_clock::time_point::min();
    //last_clock  = 0;
    align       = alignment;
    ctrl_points = {};
}

void placeholder() {}

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

void Translate::get_global_catmull_rom_point(float *pos, float *deriv) {
    int n_points = ctrl_points.size();

    float t = (curr_time.count() * 1.0f / (full_time.count()*1000)) * n_points;
    int index = floor(t);
    t = t - index;

    int indices[4];
    indices[0] = (index + n_points-1) % n_points;
    indices[1] = (indices[0]+1) % n_points;
    indices[2] = (indices[1]+1) % n_points;
    indices[3] = (indices[2]+1) % n_points;

    get_catmull_rom_point(t, ctrl_points[indices[0]], ctrl_points[indices[1]], ctrl_points[indices[2]], ctrl_points[indices[3]], pos, deriv);
}

void Translate::apply() {
    if(!dynamic) {
        glTranslatef(this->x, this->y, this->z);
    } else {
        if(start_clock == system_clock::time_point::min()) {
            start_clock = system_clock::now();
        }
        
        float pos[4];
        float deriv[4];

        get_global_catmull_rom_point(pos, deriv);

        glTranslatef(pos[0], pos[1], pos[2]);

        /* TODO: add aligning
        if(align) {
            float rotation[4][4];
            float z[3];
            float y[3];

            cross(deriv, yy, z)
        }*/

        auto new_clock = system_clock::now();
        curr_time = duration_cast<milliseconds>(new_clock - start_clock);
        if(curr_time > full_time) {
            curr_time -= full_time;
        }
    }
}
