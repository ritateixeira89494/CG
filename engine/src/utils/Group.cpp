#include "utils/Group.h"
#include "model/transforms/Translate.h"
#include <vector>
#include <iostream>
#include "GL/glut.h"
#include "model/transforms/Rotate.h"
#include "model/transforms/Scale.h"

using namespace std;

Group::Group(XMLElement *group) {
    XMLElement *transformsNode = group->FirstChildElement("transform");
    if (transformsNode != nullptr) this->transforms = getTransforms(transformsNode); // Single transform item

    XMLElement *modelsNode;
    // Check if the group has models
    if ((modelsNode = group->FirstChildElement("models")) != nullptr)
        this->models = getModels(modelsNode); // Single models item

    this->subGroups = getSubGroups(group->FirstChildElement("group")); // First child group if any
}

vector<Group *> Group::getGroups(XMLElement *firstGroup) {
    return getSubGroups(firstGroup);
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

    cout << "Element coordinates: " << x << ' ' << y << ' ' << z << ' ' << endl;

    return new coordinates{
            x,
            y,
            z,
    };

}

vector<Transform *> Group::getTransforms(XMLNode *transformsNode) {
    vector<Transform *> currentTransforms = {};

    XMLElement *transform = transformsNode->FirstChildElement();

    while (transform != nullptr) {
        // Creating the respective transforms
        Transform *t;
        const char *name = transform->Name(); // transform's name
        cout << name << endl;
        if (strcmp(name, "translate") == 0) {
            auto coords = getCoordinatesFromElement(transform);
            auto translate = new Translate(coords->x, coords->y, coords->z);
            t = translate;
            // TODO: Initialize Translate
        } else if (strcmp(name, "rotate") == 0) {
            auto coords = getCoordinatesFromElement(transform);
            auto rotate = new Rotate(transform->FloatAttribute("angle"), coords->x, coords->y, coords->z);
            t = rotate;
            // TODO: Initialize Rotate
        } else if (strcmp(name, "scale") == 0) {
            auto coords = getCoordinatesFromElement(transform);
            auto scale = new Scale(coords->x, coords->y, coords->z);
            t = scale;
            // TODO: Initialize Scale
        } else {
            cout << "Invalid transform name!" << endl;
            return currentTransforms;
        }

        currentTransforms.push_back(t);
        transform = transform->NextSiblingElement();
    }

    return currentTransforms;
}


vector<Model *> Group::getModels(XMLNode *modelsNode) {
    vector<Model *> currentModels = {};

    XMLElement *model = modelsNode->FirstChildElement("model");

    Model *m;

    while (model != nullptr) {
        const char *modelPath = model->Attribute("file");
        cout << modelPath << endl;

        const XMLElement *texture = model->FirstChildElement("texture");

        if (texture); // TODO: Pass texture path to model.

        const char *mainColor = model->Attribute("color");

        if (mainColor) {
            tuple<float, float, float> color = {0, 0, 0};
            sscanf(mainColor, "%f %f %f", &get<0>(color), &get<1>(color), &get<2>(color));
            m = new Model(modelPath, color);

        } else {
            m = new Model(modelPath);
        }

        const XMLElement *lightingColorElement = model->FirstChildElement(
                "color"); // TODO: Finish implementing the color attributes

        currentModels.push_back(m);
        model = model->NextSiblingElement();
    }
    return currentModels;
}

LightingColors Group::getColor(XMLElement *color) {
    if (!color) return {};

    return *new LightingColors();
}

vector<Group *> Group::getSubGroups(XMLElement *firstGroup) {
    vector<Group *> currentSubGroups = {};

    while (firstGroup != nullptr) {
        // cout << "Group read" << endl;

        auto g = new Group(firstGroup);

        currentSubGroups.push_back(g);
        firstGroup = firstGroup->NextSiblingElement();
    }


    return currentSubGroups;
}

void Group::render(bool cam_mode) {
    glPushMatrix();

    for (const auto transform: transforms) {
        transform->apply();
    }

    for (const auto model: models) {
        model->render(cam_mode);
    }

    for (const auto subgroup: subGroups) {
        subgroup->render(cam_mode);
    }

    glPopMatrix();
}
