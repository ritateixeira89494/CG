#include <stdio.h>

#include "model.h"
#include "triangle.h"

using namespace std;

namespace model {
    int Model::get_n_triangles() {
        return n_triangles;
    }

    int Model::load_model(char *path) {
        FILE *f = fopen(path, "r");
        if(!f){
            return -1;
        }

        GLfloat point1[3];
        GLfloat point2[3];
        GLfloat point3[3];

        fscanf(f, "%d\n", &n_triangles); 

        int mem = n_triangles * 9;
        for(int i = 0; i < mem; i+=9) {
            fscanf(f, "(%f,%f,%f);(%f,%f,%f);(%f,%f,%f)\n",
                   &point1[0], &point1[1], &point1[2],
                   &point2[0], &point2[1], &point2[2],
                   &point3[0], &point3[1], &point3[2]
                   );
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

    Model::Model(char *path) {
        n_triangles = 0;
        triangles = {};

        load_model(path);
    }
}
