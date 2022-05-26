#include "lighting/Point.h"
#include "lighting/Light.h"
#include <GL/gl.h>

namespace lighting {
    Point::Point() : Light() {
        this->posX = 0;
        this->posY = 0;
        this->posZ = 0;
    }

    Point::Point(float posX, float posY, float posZ) : Light() {
        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;
    }

    Point::Point(
            float *diffuse, float *ambient, float *specular,
            float posX, float posY, float posZ
    ) : Light(diffuse, ambient, specular) {
        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ; 
    }

    void Point::place() {
        float pos[4] = { this->posX, this->posY, this->posZ, 1.0f };
        glLightfv(GL_LIGHT0 + this->id, GL_POSITION, pos);
    }
}
