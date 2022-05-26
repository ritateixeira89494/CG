#include <cstdio>
#include <iostream>
#include <map>

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
    map<string, pair<unsigned int, long>> Model::model_ids = {}; // Path of the model -> (vbo_id, n_triangles)
    map<string, pair<unsigned int, long>> Model::normal_ids = {};

    void Model::set_lighting_colors(LightingColors colors) {
        lightingColors = colors;
    }

    long Model::get_n_triangles() const {
        return n_triangles;
    }

    long Model::load_model(char *path) {
        FILE *f = fopen(path, "r");
        if (!f) {
            cerr << "\"" << path << "\" path to model is invalid!" << endl;
            return -1;
        }

        auto str_path = string(path);
        // auto vbo_id = model_ids.find(str_path);
        if (model_ids.count(str_path) == 0) {
            glGenBuffers(1, &(vbo_buffer[0])); // Initialize vbo buffer
            glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer[0]);

            vector<float> triangles;
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

            model_ids.insert({str_path, {vbo_buffer[0], n_triangles}});
        } else {
            vbo_buffer[0] = model_ids[str_path].first;
            n_triangles = model_ids[str_path].second;
        }

        return n_triangles;
    }

    long Model::load_normal(char *path) {
        FILE *f = fopen(path, "r");
        if (!f) {
            cerr << "\"" << path << "\" path to model is invalid!" << endl;
            return -1;
        }

        auto str_path = string(path);
        if (normal_ids.count(str_path) == 0) {
            glGenBuffers(1, &vbo_buffer[1]); // Initialize vbo buffer
            glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer[1]);

            vector<float> triangles;
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

            normal_ids.insert({str_path, {vbo_buffer[1], n_triangles}});
        } else {
            vbo_buffer[1] = normal_ids[str_path].first;
            n_triangles = normal_ids[str_path].second;
        }

        return n_triangles;
    }

    Model::Model() {
        n_triangles = 0;
        lightingColors = LightingColors();
        texture_path = "";
    }

    Model::Model(const char *path) {
        n_triangles = 0;
        lightingColors = LightingColors();
        texture_path = "";
        color = {1.0, 1.0, 1.0};
        load_model(const_cast<char *>(path));
        load_normal(const_cast<char *>("box.normal"));
    }

    Model::Model(const char *path, tuple<float, float, float> color) {
        n_triangles = 0;
        lightingColors = LightingColors();
        texture_path = "";
        this->color = color;
        load_model(const_cast<char *>(path));
        load_normal(const_cast<char *>("box.normal"));
    }

    void Model::render(bool cam_mode) {
        if (!cam_mode)
            glColor3f(get<0>(color), get<1>(color), get<2>(color));

        auto dif_tup = lightingColors.diffuse;
        auto amb_tup = lightingColors.ambient;
        auto spec_tup = lightingColors.specular;
        auto emiss_tup = lightingColors.emissive;
        auto shininess = lightingColors.shininess; 

        float diffuse[4] = { get<0>(dif_tup)/256, get<1>(dif_tup)/256, get<2>(dif_tup)/256, 1 };
        float ambient[4] = { get<0>(amb_tup)/256, get<1>(amb_tup)/256, get<2>(amb_tup)/256, 1 };
        float specular[4] = { get<0>(spec_tup)/256, get<1>(spec_tup)/256, get<2>(spec_tup)/256, 1 };
        float emissive[4] = { get<0>(emiss_tup)/256, get<1>(emiss_tup)/256, get<2>(emiss_tup)/256, 1 };

        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer[0]);
        glVertexPointer(3, GL_FLOAT, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer[1]);
        glNormalPointer(GL_FLOAT, 0, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, (int) n_triangles);

    }

    Model::Model(const char *path, const string &texture_path, const LightingColors lightingColor) : Model(path) {
        this->texture_path = texture_path;
        this->lightingColors = lightingColor;
    }

}
