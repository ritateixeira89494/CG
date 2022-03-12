#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "../model/model.h"

using namespace model;

namespace interface {
    class Scene {
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
        vector<Model *> models;
        tuple<GLfloat, GLfloat, GLfloat> position;

        public:
            Scene();
            explicit Scene(char *path);
            explicit Scene(vector<Model *> models);

            void render_models();
            void move_models(GLfloat x, GLfloat y, GLfloat z);
            void rotate_models(GLfloat angle);

            tuple<GLfloat, GLfloat, GLfloat> get_position();
            void set_position(GLfloat x, GLfloat y, GLfloat z);

            GLfloat get_rotation();
            void set_rotation(GLfloat angle);

            tuple<GLfloat, GLfloat, GLfloat> get_camera_pos();
            void set_camera_pos(GLfloat x, GLfloat y, GLfloat z);

            tuple<GLfloat, GLfloat, GLfloat> get_camera_center() {
                return camera_center;
            }
            void set_camera_center(GLfloat x, GLfloat y, GLfloat z) {

            }

            tuple<GLfloat, GLfloat, GLfloat> get_up();
            void set_up(GLfloat x, GLfloat y, GLfloat z);

            GLfloat get_fov();
            void set_fov(GLfloat fov2);

            GLfloat get_near();
            void set_near(GLfloat near2);

            GLfloat get_far();
            void set_far(GLfloat far2);
    };
} // namespace interface


#endif // __SCENE_H__