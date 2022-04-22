#ifndef CG2022_GROUP_H
#define CG2022_GROUP_H

#include <vector>
#include "tinyxml2/tinyxml2.h"
#include "model/model.h"
#include "model/transforms/Transform.h"
#include "model/transforms/Translate.h"

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
         * @brief Creates a translate object from a XMLElement.
         * @note This method takes care of deciding if the translation is dynamic or not
         * 
         * @param translateNode translate group
         * @return Translate* Translate object. Dynamic or not, depending on the xml
         */
        static Translate *getTranslate(XMLElement *translateNode);

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

        Color getColor(XMLElement *color);

    public:

        /**
         * @brief Constructs the main group with the group element.
         *
         * @param group the group element.
         */
        explicit Group(XMLElement *group);

        /**
         * Renders all transforms, models and subgroups.
         */
        void render();

        /**
         * @brief Gets the first group and all its siblings groups.
         *
         * @param firstGroup the first group element.
         * @return vector with all groups of the element.
         */
        static vector<Group *> getGroups(XMLElement *firstGroup);

};


#endif //CG2022_GROUP_H
