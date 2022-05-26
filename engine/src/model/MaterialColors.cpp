#include "model/MaterialColors.h"
#include <GL/gl.h>
#include <algorithm>

using namespace std;

MaterialColors::MaterialColors(
        const int *diffuse, const int *ambient, 
        const int *specular, const int *emissive, 
        int shininess
) {
    for(int i = 0; i < 4; i++) {
        // Before storing the values we normalize them.
        // Since we can't have zeroes in the vectors, because of the multiplications
        // OpenGL does, we do a max(val, 1).
        this->diffuse[i]   = (float) max(diffuse[i], 1)  / 255;
        this->ambient[i]   = (float) max(ambient[i], 1)  / 255;
        this->specular[i]  = (float) max(specular[i], 1) / 255;
        this->emissive[i]  = (float) max(emissive[i], 1) / 255;
    }
    this->shininess = shininess;
}

void MaterialColors::apply_color() {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissive);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
