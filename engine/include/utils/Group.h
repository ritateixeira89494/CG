#ifndef CG2022_GROUP_H
#define CG2022_GROUP_H

#include <vector>
#include "tinyxml2/tinyxml2.h"
#include "model/model.h"
#include "model/transforms/Transform.h"

using namespace tinyxml2;
using namespace std;
using namespace model;

class Group {

    private:

        /**
         * Vector of the transforms of the group.
         */
        vector<Transform *> transforms;

        /**
         * Vector of the models of the group.
         */
        vector<Model *> models;

        /**
         * Vector of the subgroups of the group.
         */
        vector<Group *> subGroups;

        /**
         * @brief Gets the transforms of the transforms node.
         *
         * @param transformsNode the transforms node.
         * @return vector with all transforms of the node.
         */
        static vector<Transform *> getTransforms(XMLNode *transformsNode);

        /**
         * @brief Gets the models of the models node.
         *
         * @param modelsNode the models node.
         * @return vector with all models of the node.
         */
        static vector<Model *> getModels(XMLNode *modelsNode);

        /**
         * @brief Gets the first group and all its siblings groups.
         *
         * @param firstGroup the first group element.
         * @return vector with all groups of the element.
         */
        static vector<Group *> getSubGroups(XMLElement *firstGroup);

        LightingColors getColor(XMLElement *color);

    public:

        /**
         * @brief Constructs the main group with the group element.
         *
         * @param group the group element.
         */
        explicit Group(XMLElement *group);

        /**
         * @brief Renders all transforms, models and subgroups.
         * 
         * @param cam_mode bool telling if camera mode is active or not
         */
        void render(bool cam_mode);

        /**
         * @brief Gets the first group and all its siblings groups.
         *
         * @param firstGroup the first group element.
         * @return vector with all groups of the element.
         */
        static vector<Group *> getGroups(XMLElement *firstGroup);

};


#endif //CG2022_GROUP_H
