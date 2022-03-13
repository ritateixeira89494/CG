#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
#include "interface/scene.h"
#include "tinyxml2/tinyxml2.h"
#include "utils/coords.h"

using namespace tinyxml2;

namespace interface {
    Scene::Scene() {
        models = {};
        set_position(0, 0, 0);
        set_camera_pos(15, 10, 15);
        set_up(0, 1, 0);
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

        XMLElement *world = doc.FirstChildElement();

        // Parsing camera
        XMLElement *camera = world->FirstChildElement("camera");

        // Position coordinates
        XMLElement *positionElement = camera->FirstChildElement("position");
        coordinates positionCoord = getCoordinatesFromElement(positionElement);
        set_camera_pos(positionCoord.x, positionCoord.y, positionCoord.z);

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
        set_fov(60);
        set_near(1);
        set_far(1000);

        for (Model *model: m) {
            models.push_back(model);
        }
    }

    void Scene::render_models() {
        glBegin(GL_TRIANGLES);
        for (Model *model: models) {
            vector<Triangle *> triangles = model->get_triangles();
            for (Triangle *tri: triangles) {
                tuple<float, float, float> p1 = tri->get_p1();
                tuple<float, float, float> p2 = tri->get_p2();
                tuple<float, float, float> p3 = tri->get_p3();

                glVertex3f((get<0>(p1)*scale) + get<0>(position), (get<1>(p1)*scale) + get<1>(position), (get<2>(p1)*scale) + get<2>(position));
                glVertex3f((get<0>(p2)*scale) + get<0>(position), (get<1>(p2)*scale) + get<1>(position), (get<2>(p2)*scale) + get<2>(position));
                glVertex3f((get<0>(p3)*scale) + get<0>(position), (get<1>(p3)*scale) + get<1>(position), (get<2>(p3)*scale) + get<2>(position));
            }
        }
        glEnd();
    }

    void Scene::move_models(float x, float y, float z) {
        get<0>(position) += x;
        get<1>(position) += y;
        get<2>(position) += z;
    }

    void Scene::rotate_models(float angle_alpha, float angle_beta) {
        m_rotation_alpha += angle_alpha;
        m_rotation_beta += angle_beta;
    }

    void Scene::move_camera(float x, float y, float z) {
        get<0>(camera_center) += x;
        get<1>(camera_center) += y;
        get<2>(camera_center) += z;
    }

    void Scene::rotate_camera(float angle_alpha, float angle_beta) {
        alpha += angle_alpha;
        beta  += angle_beta;

        if(beta > 3.14)
            beta = 3.14;
        else if(beta < 0.01)
            beta = 0.01;
    }

    void Scene::change_scale(float val) {
        scale += val;
        if(scale < 0.1)
            scale = 0.1;
    }

    void Scene::zoom(float zoom) {
        radius += zoom;
        if(radius < 0.1)
            radius = 0.1;
    }

    tuple<float, float, float> Scene::get_position() {
        return position;
    }

    void Scene::set_position(float x, float y, float z) {
        position = make_tuple(x, y, z);
    }

    tuple<float, float, float> Scene::get_camera_pos() {
        auto pos = spherical2cartesian(radius, alpha, beta) ;
        auto cam_center = get_camera_center();
        
        get<0>(pos) += get<0>(cam_center);
        get<1>(pos) += get<1>(cam_center);
        get<2>(pos) += get<2>(cam_center);

        return pos;
    }

    void Scene::set_camera_pos(float x, float y, float z) {
        auto coords = cartesian2spherical(x,y,z);

        radius = get<0>(coords);
        alpha = get<1>(coords);
        beta = get<2>(coords);
    }

    tuple<float, float, float> Scene::get_camera_center() {
        return camera_center;
    }

    void Scene::set_camera_center(float x, float y, float z) {
        camera_center = make_tuple(x,y,z);
    } 

    tuple<float, float, float> Scene::get_up() {
        return up;
    }

    void Scene::set_up(float x, float y, float z) {
        up = make_tuple(x, y, z);
    }

    float Scene::get_fov() {
        return fov;
    }

    void Scene::set_fov(float fov2) {
        fov = fov2;
    }

    float Scene::get_near() {
        return near;
    }

    void Scene::set_near(float near2) {
        near = near2;
    }

    float Scene::get_far() {
        return far;
    }

    void Scene::set_far(float far2) {
        far = far2;
    }

    float Scene::get_model_rotation_alpha() {
        return m_rotation_alpha;
    }

    float Scene::get_model_rotation_beta() {
        return m_rotation_beta;
    }

    float Scene::get_scale() {
        return scale;
    }
}