#include "lighting/Directional.h"
#include "lighting/Light.h"
#include <GL/gl.h>

namespace lighting {
    Directional::Directional(
            float diffuse[4], float ambient[4], float specular[4],
            float dirX, float dirY, float dirZ    
    ) : Light(diffuse, ambient, specular) {
        this->dirX = dirX;
        this->dirY = dirY;
        this->dirZ = dirZ;
    }

    Directional::Directional(float dirX, float dirY, float dirZ) : Light() {
        this->dirX = dirX;
        this->dirY = dirY;
        this->dirZ = dirZ;
    }

    void Directional::place() {
        float pos[4] = { dirX, dirY, dirZ, 0.0f };
        glLightfv(GL_LIGHT0 + this->id, GL_POSITION, pos);
        glLightf(GL_LIGHT0 + this->id, GL_CONSTANT_ATTENUATION, 0.2);
        glLightf(GL_LIGHT0 + this->id, GL_LINEAR_ATTENUATION, 0);
        glLightf(GL_LIGHT0 + this->id, GL_QUADRATIC_ATTENUATION, 0);
    }
}
