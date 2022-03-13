#include <stdio.h>
#include <iostream>

#include "model/model.h"
#include "model/triangle.h"

using namespace std;

namespace model {
    int Model::get_n_triangles() {
        return n_triangles;
    }

    int Model::load_model(char *path) {
        FILE *f = fopen(path, "r");
        if (!f) {
            cerr << "Invalid model path!" << endl;
            return -1;
        }

        float point1[3];
        float point2[3];
        float point3[3];
        while (
                fscanf(f, "(%f,%f,%f);(%f,%f,%f);(%f,%f,%f)\n",
                       &point1[0], &point1[1], &point1[2],
                       &point2[0], &point2[1], &point2[2],
                       &point3[0], &point3[1], &point3[2]
                ) != EOF
                ) {
            triangles.push_back(new Triangle(
                    point1[0], point1[1], point1[2],
                    point2[0], point2[1], point2[2],
                    point3[0], point3[1], point3[2]
            ));
        }

        return n_triangles;
    }

    vector<Triangle *> Model::get_triangles() {
        return triangles;
    }

    Model::Model() {
        n_triangles = 0;
        triangles = {};
    }

    Model::Model(const char *path) {
        n_triangles = 0;
        triangles = {};

        load_model(const_cast<char *>(path));
    }
}
