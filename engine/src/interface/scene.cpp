#include "scene.h"

namespace interface {
    Scene::Scene() {
        models = {};
    }

    // TODO: Code this function
    Scene::Scene(char *path) {
        models = {};
        Model *m = new Model(path);

        models.push_back(m);
    }

    Scene::Scene(vector<Model *> m) {
        models = {};
        
        for(Model *model : m) {
            models.push_back(model);
        }
    }

    void Scene::render_models() {
        glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 1);
        for(Model *model : models) {
            vector<Triangle *> triangles = model->get_triangles();
            for(Triangle *tri : triangles) {
                tuple<GLfloat, GLfloat, GLfloat> p1 = tri->get_p1();
                tuple<GLfloat, GLfloat, GLfloat> p2 = tri->get_p2();
                tuple<GLfloat, GLfloat, GLfloat> p3 = tri->get_p3();

                glVertex3f(get<0>(p1) + get<0>(position), get<1>(p1) + get<1>(position), get<2>(p1) + get<2>(position));
                glVertex3f(get<0>(p2) + get<0>(position), get<1>(p2) + get<1>(position), get<2>(p2) + get<2>(position));
                glVertex3f(get<0>(p3) + get<0>(position), get<1>(p3) + get<1>(position), get<2>(p3) + get<2>(position));
            }
        }
        glEnd();
    }

    void Scene::move_models(GLfloat x, GLfloat y, GLfloat z) {
        get<0>(position)+=x;
        get<1>(position)+=y;
        get<2>(position)+=z;
    }
}