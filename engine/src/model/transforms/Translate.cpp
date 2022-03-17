#include "model/transforms/Translate.h"
#include "model/transforms/Transform.h"
#include "GL/glut.h"

Translate::Translate(float x, float y, float z) : Transform(x, y, z) {

}

void Translate::apply() {
    glTranslatef(this->x, this->y, this->z);
}
