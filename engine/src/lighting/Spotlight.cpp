#include "lighting/Spotlight.h"
#include "lighting/Light.h"
#include <GL/gl.h>

namespace lighting {
    Spotlight::Spotlight(
            float posX, float posY, float posZ,
            float dirX, float dirY, float dirZ,
            float cutoff
    ) : Light() {
        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;

        this->dirX = dirX;
        this->dirY = dirY;
        this->dirZ = dirZ;

        this->cutoff = cutoff;
    }

    Spotlight::Spotlight(
            float *diffuse, float *ambient, float *specular,
            float posX, float posY, float posZ,
            float dirX, float dirY, float dirZ,
            float cutoff
    ) : Light(diffuse, ambient, specular) {
        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;

        this->dirX = dirX;
        this->dirY = dirY;
        this->dirZ = dirZ;

        this->cutoff = cutoff;
    }


    void Spotlight::place() {
        float pos[4] = { this->posX, this->posY, this->posZ, 1.0f };
        float dir[4] = { this->dirX, this->dirY, this->dirZ, 0.0f };

        glLightfv(GL_LIGHT0 + this->id, GL_POSITION, pos);
        glLightfv(GL_LIGHT0 + this->id, GL_SPOT_DIRECTION, dir);
        glLightf(GL_LIGHT0 + this->id, GL_SPOT_CUTOFF, this->cutoff);
    }
}
