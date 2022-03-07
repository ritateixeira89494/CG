#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "../model/model.h"

using namespace model;

namespace interface {
    class Scene {
        vector<Model *> models;
        tuple<GLfloat, GLfloat, GLfloat> position;

        void render_scene();
        public:
            Scene();
            Scene(char *path);
            Scene(vector<Model *> models);
            void render_models();
            void move_models(GLfloat x, GLfloat y, GLfloat z);
    };
} // namespace interface


#endif // __SCENE_H__