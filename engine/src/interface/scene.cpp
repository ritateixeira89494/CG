#include <iostream>
#include "scene.h"
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace interface {
    Scene::Scene() {
        models = {};
        set_position(0, 0, 0);
        set_camera_pos(15, 10, 15);
        set_up(0, 1, 0);
        set_rotation(0);
        set_fov(60);
        set_near(1);
        set_far(1000);
    }

    typedef struct coordinates {
        float x;
        float y;
        float z;
    } *Coord;

    struct coordinates getCoordinatesFromElement(XMLElement *element) {

        float x;
        float y;
        float z;

        element->QueryAttribute("x", &x);
        element->QueryAttribute("y", &y);
        element->QueryAttribute("z", &z);

        cout << "Element coordinates: " << x << ' ' << y << ' ' << z << ' ' << endl;

        return coordinates{
                x,
                y,
                z,
        };

    }


    // TODO: Code this function
    Scene::Scene(char *path) {
        models = {};
        XMLDocument doc;

        if (doc.LoadFile(path) != tinyxml2::XML_SUCCESS) {
            cerr << "Something went wrong with the xml file!" << endl;
            throw; // TODO: handle error here;
        }

        set_position(0, 0, 0);
        set_rotation(0);

        XMLElement *world = doc.FirstChildElement();

        // Parsing camera
        XMLElement *camera = world->FirstChildElement("camera");

        // Position coordinates
        XMLElement *positionElement = camera->FirstChildElement("position");
        coordinates positionCoord = getCoordinatesFromElement(positionElement);
        set_camera_pos(positionCoord.x, positionCoord.x, positionCoord.z);

        // LookAt coordinates
        XMLElement *lookAt = camera->FirstChildElement("lookAt");
        coordinates lookAtCoord = getCoordinatesFromElement(lookAt);
        set_camera_center(lookAtCoord.x, lookAtCoord.y, lookAtCoord.z); //TODO: Function call missing

        // Up coordinates
        XMLElement *upElement = camera->FirstChildElement("up");
        coordinates upCoord = getCoordinatesFromElement(upElement);
        set_up(upCoord.x, upCoord.y, upCoord.z);

        // Projection parameters
        XMLElement *projection = camera->FirstChildElement("projection");

        projection->QueryAttribute("fov", &fov);
        projection->QueryAttribute("near", &near);
        projection->QueryAttribute("far", &far);

        cout << "Projection parameters: fov=" << fov << " near=" << near << " far=" << far << endl;

        // Models

        XMLNode *modelsNode = world->FirstChildElement("group")->FirstChild();


        XMLElement *model = modelsNode->FirstChildElement("model");

        while (model != nullptr) {

            const char *modelPath = model->Attribute("file");
            cout << modelPath << endl;

            auto *m = new Model(modelPath);

            models.push_back(m);
            model = model->NextSiblingElement();
        }
    }

    Scene::Scene(vector<Model *> m) {
        models = {};
        set_position(0, 0, 0);
        set_camera_pos(15, 10, 15);
        set_up(0, 1, 0);
        set_rotation(0);
        set_fov(60);
        set_near(1);
        set_far(1000);

        for (Model *model: m) {
            models.push_back(model);
        }
    }

    void Scene::render_models() {
        glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 1);
        for (Model *model: models) {
            vector<Triangle *> triangles = model->get_triangles();
            for (Triangle *tri: triangles) {
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
        get<0>(position) += x;
        get<1>(position) += y;
        get<2>(position) += z;
    }

    void Scene::rotate_models(GLfloat angle) {
        rotation += angle;
    }

    tuple<GLfloat, GLfloat, GLfloat> Scene::get_position() {
        return position;
    }

    void Scene::set_position(GLfloat x, GLfloat y, GLfloat z) {
        position = make_tuple(x, y, z);
    }

    GLfloat Scene::get_rotation() {
        return rotation;
    }

    void Scene::set_rotation(GLfloat angle) {
        rotation = angle;
    }

    tuple<GLfloat, GLfloat, GLfloat> Scene::get_camera_pos() {
        return camera_pos;
    }

    void Scene::set_camera_pos(GLfloat x, GLfloat y, GLfloat z) {
        camera_pos = make_tuple(x, y, z);
    }

    tuple<GLfloat, GLfloat, GLfloat> Scene::get_up() {
        return up;
    }

    void Scene::set_up(GLfloat x, GLfloat y, GLfloat z) {
        up = make_tuple(x, y, z);
    }

    GLfloat Scene::get_fov() {
        return fov;
    }

    void Scene::set_fov(GLfloat fov2) {
        fov = fov2;
    }

    GLfloat Scene::get_near() {
        return near;
    }

    void Scene::set_near(GLfloat near2) {
        near = near2;
    }

    GLfloat Scene::get_far() {
        return far;
    }

    void Scene::set_far(GLfloat far2) {
        far = far2;
    }
}