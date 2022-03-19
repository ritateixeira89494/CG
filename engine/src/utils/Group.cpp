#include "utils/Group.h"
#include "model/transforms/Translate.h"
#include <vector>
#include <iostream>
#include "GL/glut.h"

using namespace std;

Group::Group(XMLElement *group) {
    XMLElement *transformsNode = group->FirstChildElement("transform");
    if (transformsNode != nullptr) this->transforms = getTransforms(transformsNode);

    XMLElement *modelsNode = group->FirstChildElement("models");
    // Check if the group has models
    if ((modelsNode = group->FirstChildElement("models")) != nullptr) {
        this->models = getModels(modelsNode);

    } else { // If the group has no models it has subgroups
        this->subGroups = getSubGroups(group);
    }
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
    vector<Transform *> currentTransforms = *new vector<Transform *>;

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
            // TODO: Initialize Rotate
        } else if (strcmp(name, "scale") == 0) {
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
    vector<Model *> currentModels = *new vector<Model *>;

    XMLElement *model = modelsNode->FirstChildElement("model");

    while (model != nullptr) {

        const char *modelPath = model->Attribute("file");
        cout << modelPath << endl;

        auto m = new Model(modelPath);

        currentModels.push_back(m);
        model = model->NextSiblingElement();
    }
    return currentModels;
}

vector<Group *> Group::getSubGroups(XMLNode *mainGroup) {
    vector<Group *> currentSubGroups = *new vector<Group *>;

    return currentSubGroups;
}

void Group::render() {
    glPushMatrix();

    for (const auto transform: transforms) {
        transform->apply();
    }

    for (const auto model: models) {
        cout << model->get_n_triangles() << endl;
        model->render();
    }

    /*

     */

    glPopMatrix();
}
