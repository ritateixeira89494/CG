#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "../model/model.h"

using namespace model;

namespace interface {
    class Scene {
        vector<Model *> models;
        void render_scene();
        public:
            Scene();
            Scene(char *path);
            Scene(vector<Model *> models);
            void render_models();
    };
} // namespace interface


#endif // __SCENE_H__