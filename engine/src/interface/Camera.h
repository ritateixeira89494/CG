#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "../model/model.h"

namespace Camera {
    class Camera {
        tuple<GLfloat, GLfloat, GLfloat> camera_pos;
        tuple<GLfloat, GLfloat, GLfloat> camera_center;
        tuple<GLfloat, GLfloat, GLfloat> up;
        GLfloat rotation;
        GLfloat fov;
        GLfloat near;
        GLfloat far;

        GLfloat alpha;
        GLfloat beta;
        GLfloat radio;

        public:
            Camera();


    };
}


#endif //ENGINE_CAMERA_H
