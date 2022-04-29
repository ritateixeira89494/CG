#include "model/transforms/Rotate.h"
#include "model/transforms/Transform.h"
#include "GL/glut.h"

Rotate::Rotate(float angle, float x, float y, float z) : Transform(x, y, z) {
    dynamic = false;
    this->angle = angle;
    start = 0;
}

Rotate::Rotate(int t, float x, float y, float z) : Transform(x, y, z) {
    dynamic = true;
    full_time = t * 1000;
    start = 0;
}

void Rotate::apply() {
    if(!dynamic) {
        glRotatef(angle, this->x, this->y, this->z);
    } else {
        if(start == 0) {
            start = glutGet(GLUT_ELAPSED_TIME);
        }
        int cur_time = (glutGet(GLUT_ELAPSED_TIME) - start) % full_time;

        float cur_rotation = (cur_time * 360.0f) / (full_time);

        glRotatef(cur_rotation, x, y, z);
    }
}

void Rotate::set_dynamic(bool dynamic) {
    this->dynamic = dynamic;
}
bool Rotate::get_dynamic() {
    return dynamic;
}

void Rotate::set_angle(float angle) {
    this->angle = angle;
}
float Rotate::get_angle() {
    return angle;
}

void Rotate::set_start(int start) {
    this->start = start;
}
int Rotate::get_start() {
    return start;
}