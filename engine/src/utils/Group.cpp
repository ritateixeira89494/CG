#include "utils/Group.h"
#include "model/transforms/Translate.h"
#include <vector>
#include <iostream>
#include "GL/glut.h"
#include "model/transforms/Rotate.h"
#include "model/transforms/Scale.h"

//TODO Change this
#include <stdlib.h>

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

    return new coordinates{
            x,
            y,
            z,
    };

}

Translate *Group::getTranslate(XMLElement *translateNode) {
    int time;
    auto coords = getCoordinatesFromElement(translateNode);

    if (translateNode->QueryIntAttribute("time", &time) != XML_SUCCESS) {
        return new Translate(coords->x, coords->y, coords->z);
    } else {
        bool align;
        translateNode->QueryBoolAttribute("align", &align);
        int segments;
        if (translateNode->QueryIntAttribute("segments", &segments) != XML_SUCCESS) {
            segments = 200;
        }
        bool draw;
        if (translateNode->QueryBoolAttribute("draw", &draw) != XML_SUCCESS) {
            draw = false;
        }
        int offset;
        if (translateNode->QueryIntAttribute("offset", &offset) != XML_SUCCESS) {
            offset = 0;
        }

        vector<tuple<float, float, float>> points = {};
        XMLElement *lol = translateNode->FirstChildElement();
        while (lol != nullptr) {
            float x, y, z;
            lol->QueryFloatAttribute("x", &x);
            lol->QueryFloatAttribute("y", &y);
            lol->QueryFloatAttribute("z", &z);

            auto point = make_tuple(x, y, z);

            points.push_back(point);
            lol = lol->NextSiblingElement();
        }
        return new Translate(time, align, draw, offset, segments, points);
    }
}

Rotate *Group::getRotate(XMLElement *rotateNode) {
    int time;
    auto coords = getCoordinatesFromElement(rotateNode);

    if (rotateNode->QueryIntAttribute("time", &time) != XML_SUCCESS) {
        float angle = rotateNode->FloatAttribute("angle");
        return new Rotate(angle, coords->x, coords->y, coords->z);
    } else {
        return new Rotate(time, coords->x, coords->y, coords->z);
    }
}

vector<Transform *> Group::getTransforms(XMLNode *transformsNode) {
    vector<Transform *> currentTransforms = {};

    XMLElement *transform = transformsNode->FirstChildElement();

    while (transform != nullptr) {
        // Creating the respective transforms
        Transform *t;
        const char *name = transform->Name(); // transform's name
        if (strcmp(name, "translate") == 0) {
            t = getTranslate(transform);
        } else if (strcmp(name, "rotate") == 0) {
            t = getRotate(transform);
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

        auto g = new Group(firstGroup);

        currentSubGroups.push_back(g);
        firstGroup = firstGroup->NextSiblingElement();
    }


    return currentSubGroups;
}

void Group::render(bool cam_mode) {
    glPushMatrix();

    for (const auto transform: transforms) {
        Translate *translate = dynamic_cast<Translate *>(transform);
        if (translate != nullptr) {
            translate->draw_curve();
        }
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
