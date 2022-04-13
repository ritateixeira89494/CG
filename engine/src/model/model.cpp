#include <cstdio>
#include <iostream>

#include "model/model.h"
#include "model/triangle.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glew.h>
#include <GL/glut.h>

#endif

using namespace std;

namespace model {
    long Model::get_n_triangles() const {
        return n_triangles;
    }

    long Model::load_model(char *path) {
        FILE *f = fopen(path, "r");
        if (!f) {
            cerr << "Invalid model path!" << endl;
            return -1;
        }

        glGenBuffers(1, vbo_buffer); // Initialize vbo buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer[0]);

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

            triangles.push_back(point1[0]);
            triangles.push_back(point1[1]);
            triangles.push_back(point1[2]);

            triangles.push_back(point2[0]);
            triangles.push_back(point2[1]);
            triangles.push_back(point2[2]);

            triangles.push_back(point3[0]);
            triangles.push_back(point3[1]);
            triangles.push_back(point3[2]);
        }
        n_triangles = (long) (triangles.size() / 3);

        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (triangles.size() * sizeof(float)), triangles.data(),
                     GL_STATIC_DRAW);

        return n_triangles;
    }

    vector<float> Model::get_triangles() {
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

    void Model::render(bool cam_mode) {
        if (!cam_mode)
            glColor3f(get<0>(color), get<1>(color), get<2>(color));

        glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer[0]);

        glVertexPointer(3, GL_FLOAT, 0, nullptr);

        glDrawArrays(GL_TRIANGLES, 0, triangles.size());
    }

    Model::Model(const char *path, const string &texture_path, const LightingColors lightingColor) : Model(path) {
        this->texture_path = texture_path;
        this->lightingColors = lightingColor;
    }

}
