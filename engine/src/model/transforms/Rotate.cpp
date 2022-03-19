#include "model/transforms/Rotate.h"
#include "model/transforms/Transform.h"
#include "GL/glut.h"

Rotate::Rotate(float angle, float x, float y, float z) : Transform(x, y, z) {
    this->angle = angle;
}

void Rotate::apply() {
    glRotatef(angle, this->x, this->y, this->z);
}
