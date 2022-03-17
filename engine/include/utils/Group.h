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
        // group1 -> transform1, models1, group2
        vector<Transform> transformations;
        vector<Model> models;
        vector<Group> subGroups;


    public:
        Group(XMLNode *group);
};


#endif //CG2022_GROUP_H
