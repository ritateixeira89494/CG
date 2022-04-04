#include <cstdio>
#include <iostream>

#include "model/model.h"
#include "model/triangle.h"
#include "GL/glut.h"

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
            triangles.emplace_back(
                    point1[0], point1[1], point1[2],
                    point2[0], point2[1], point2[2],
                    point3[0], point3[1], point3[2]
            );
        }
        n_triangles = triangles.size();

        return n_triangles;
    }

    vector<Triangle> Model::get_triangles() {
        return triangles;
    }

    Model::Model() {
        n_triangles = 0;
        lightingColors = LightingColors();
        texture_path = "";
        triangles = {};
    }

    Model::Model(const char *path) {
        n_triangles = 0;
        triangles = {};
        lightingColors = LightingColors();
        texture_path = "";
        color = {1.0, 1.0, 1.0};
        load_model(const_cast<char *>(path));
    }

    Model::Model(const char *path, tuple<float, float, float> color) {
        n_triangles = 0;
        triangles = {};
        lightingColors = LightingColors();
        texture_path = "";
        this->color = color;
        load_model(const_cast<char *>(path));
    }

    void Model::render() {
        glColor3f(get<0>(color), get<1>(color), get<2>(color));

        glBegin(GL_TRIANGLES);
        for (Triangle tri: triangles) {
            tuple<float, float, float> p1 = tri.get_p1();
            tuple<float, float, float> p2 = tri.get_p2();
            tuple<float, float, float> p3 = tri.get_p3();

            glVertex3f(get<0>(p1), get<1>(p1), get<2>(p1));
            glVertex3f(get<0>(p2), get<1>(p2), get<2>(p2));
            glVertex3f(get<0>(p3), get<1>(p3), get<2>(p3));
        }
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
    }

    Model::Model(const char *path, const string &texture_path, const LightingColors lightingColor) : Model(path) {
        this->texture_path = texture_path;
        this->lightingColors = lightingColor;
    }

}
