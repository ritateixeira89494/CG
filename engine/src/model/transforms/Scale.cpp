#include "model/transforms/Scale.h"
#include "model/transforms/Transform.h"
#include "GL/glut.h"

Scale::Scale(float x, float y, float z) : Transform(x, y, z) {

}

void Scale::apply() {
    glScalef(this->x, this->y, this->z);
}