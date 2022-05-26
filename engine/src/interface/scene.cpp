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
#include "lighting/Directional.h"
#include "lighting/Point.h"

using namespace tinyxml2;

namespace interface {
    Scene::Scene() {
        groups = {};
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

    Coord getCoordinatesFromElement(XMLElement *element) {
        float x;
        float y;
        float z;

        element->QueryAttribute("x", &x);
        element->QueryAttribute("y", &y);
        element->QueryAttribute("z", &z);

        return new coordinates{
                x,
                y,
                z,
        };

    }

    void Scene::load_lights(XMLElement *lights) {
        XMLElement *light = lights->FirstChildElement("light");
        while(light != nullptr) {
            const char *type = light->Attribute("type");

            if(strcmp(type,"directional") == 0) {
                float dirX, dirY, dirZ;
                light->QueryFloatAttribute("dirX", &dirX);
                light->QueryFloatAttribute("dirY", &dirY);
                light->QueryFloatAttribute("dirZ", &dirZ);

                Directional *l = new Directional(dirX, dirY, dirZ);
                light_list.push_back((Light *) l);
            } else if(strcmp(type, "point") == 0) {
                float posX, posY, posZ;
                light->QueryFloatAttribute("posX", &posX);
                light->QueryFloatAttribute("posY", &posY);
                light->QueryFloatAttribute("posZ", &posZ);
                Point *p = new Point(posX,posY,posZ);
                light_list.push_back((Light *) p);
            }
            else if(strcmp(type, "spotlight") == 0) {}
            light = light->NextSiblingElement();
        }
    }

    Scene::Scene(const char *path) {
        XMLDocument doc;

        if (doc.LoadFile(path) != tinyxml2::XML_SUCCESS) {
            cerr << "Something went wrong with the xml file!" << endl;
            exit(1);
            throw; // TODO: handle error here;
        }

        set_position(0, 0, 0);

        XMLElement *world = doc.FirstChildElement();

        // Parsing camera
        XMLElement *camera = world->FirstChildElement("camera");

        // Position coordinates
        XMLElement *positionElement = camera->FirstChildElement("position");
        Coord positionCoord = getCoordinatesFromElement(positionElement);
        set_camera_pos(positionCoord->x, positionCoord->y, positionCoord->z);

        // LookAt coordinates
        XMLElement *lookAt = camera->FirstChildElement("lookAt");
        Coord lookAtCoord = getCoordinatesFromElement(lookAt);
        set_camera_center(lookAtCoord->x, lookAtCoord->y, lookAtCoord->z); //TODO: Function call missing

        // Up coordinates
        XMLElement *upElement = camera->FirstChildElement("up");
        Coord upCoord = getCoordinatesFromElement(upElement);
        set_up(upCoord->x, upCoord->y, upCoord->z);

        // Projection parameters
        XMLElement *projection = camera->FirstChildElement("projection");

        if (projection) {
            projection->QueryAttribute("fov", &fov);
            projection->QueryAttribute("near", &near);
            projection->QueryAttribute("far", &far);

        } else { // Default values for projection
            fov = 60;
            near = 1;
            far = 1000;
        }

        XMLElement *lights = world->FirstChildElement("lights");
        load_lights(lights);

        // Groups
        XMLElement *groupElement = world->FirstChildElement("group");
        this->groups = Group::getGroups(groupElement);
    }

    Perspective Scene::get_perspective() {
        auto cam_pos = get_camera_pos();
        auto cam_center = get_camera_center();
        auto up = get_up();

        return Perspective(
                get<0>(cam_pos), get<1>(cam_pos), get<2>(cam_pos),
                get<0>(cam_center), get<1>(cam_center), get<2>(cam_center),
                get<0>(up), get<1>(up), get<2>(up)
        );
    }

    void Scene::place_lights() {
        for(Light *l: light_list) {
            l->place();
        }
    }

    void Scene::render_models(bool cam_mode) {
        for (auto group: groups) {
            group->render(cam_mode);
        }
    }

    void Scene::move_models(float angle) {
        get<0>(position) += 0.1 * sin(alpha + angle);
        get<2>(position) += 0.1 * cos(alpha + angle);
    }

    void Scene::rotate_models(float angle_alpha, float angle_beta) {
        m_rotation_alpha += angle_alpha;
        m_rotation_beta += angle_beta;
    }

    Perspective Scene::move_camera(float angle) {
        get<0>(camera_center) += 0.1f * sin(alpha + angle);
        get<2>(camera_center) += 0.1f * cos(alpha + angle);

        return get_perspective();
    }

    Perspective Scene::rotate_camera(float angle_alpha, float angle_beta) {
        alpha += angle_alpha;
        beta += angle_beta;

        if (beta > 3.14)
            beta = 3.14;
        else if (beta < 0.01)
            beta = 0.01;

        return get_perspective();
    }

    void Scene::change_scale(float val) {
        scale += val;
        if (scale < 0.1)
            scale = 0.1;
    }

    Perspective Scene::zoom(float zoom) {
        radius += zoom;
        if (radius < 0.1)
            radius = 0.1;

        return get_perspective();
    }

    tuple<float, float, float> Scene::get_position() {
        return position;
    }

    void Scene::set_position(float x, float y, float z) {
        position = make_tuple(x, y, z);
    }

    tuple<float, float, float> Scene::get_camera_pos() {
        auto pos = spherical2cartesian(radius, alpha, beta);
        auto cam_center = get_camera_center();

        get<0>(pos) += get<0>(cam_center);
        get<1>(pos) += get<1>(cam_center);
        get<2>(pos) += get<2>(cam_center);

        return pos;
    }

    void Scene::set_camera_pos(float x, float y, float z) {
        auto coords = cartesian2spherical(x, y, z);

        radius = get<0>(coords);
        alpha = get<1>(coords);
        beta = get<2>(coords);
    }

    tuple<float, float, float> Scene::get_camera_center() {
        return camera_center;
    }

    void Scene::set_camera_center(float x, float y, float z) {
        camera_center = make_tuple(x, y, z);
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

    float Scene::get_radius() {
        return radius;
    }

    void Scene::set_radius(float rad) {
        radius = rad;
    }
}
