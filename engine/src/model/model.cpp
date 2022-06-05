#include <cstdio>
#include <iostream>
#include <map>

#include "model/MaterialColors.h"
#include "model/model.h"
#include "model/triangle.h"
#include "utils/misc.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glew.h>
#include <GL/glut.h>

#endif

#include <IL/il.h>
#include <fstream>
#include <cstring>

using namespace std;

namespace model {
    map<string, tuple<unsigned int, long, unsigned int>> Model::model_ids = {}; // Path of the model -> (vbo_id, n_triangles, tex_id)
    map<string, pair<unsigned int, long>> Model::normal_ids = {};
    map<string, unsigned int> Model::texture_ids = {}; // Texture path -> id of texture

    void Model::set_material_colors(MaterialColors colors) {
        materialColors = colors;
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

            // Reading the .3d file
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

            // Vertices
            glGenBuffers(1, &vbo_buffer[0]); // Initialize vbo buffer
            glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer[0]);
            glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (triangles.size() * sizeof(float)), triangles.data(),
                         GL_STATIC_DRAW);

            // Reading the .text file
            string str_path = string(path);
            vector<float> t = parseTextureCoordinates(
                    const_cast<char *>((str_path.substr(0, str_path.length() - 3) + ".text").c_str()));

            // Texture coordenates
            glGenBuffers(1, &model_tex_id);
            glBindBuffer(GL_ARRAY_BUFFER, model_tex_id);
            glBufferData(GL_ARRAY_BUFFER, (long) (sizeof(float) * 2 * t.size()), t.data(), GL_STATIC_DRAW);

            model_ids.insert({str_path, {vbo_buffer[0], n_triangles, model_tex_id}});
        } else {
            vbo_buffer[0] = get<0>(model_ids[str_path]);
            n_triangles = get<1>(model_ids[str_path]);
            model_tex_id = get<2>(model_ids[str_path]);
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
        materialColors = MaterialColors();
        texture_path = "";
    }

    Model::Model(const char *path) {
        n_triangles = 0;
        materialColors = MaterialColors();
        texture_path = "";
        color = {1.0, 1.0, 1.0};

        string normal_path = replace_extension(path, "normal");

        load_model(const_cast<char *>(path));
        load_normal(const_cast<char *>(normal_path.c_str()));
    }

    Model::Model(const char *path, tuple<float, float, float> color) : Model(path) {
        this->color = color;
    }

    void Model::render(bool cam_mode) {
        if (!cam_mode)
            glColor3f(get<0>(color), get<1>(color), get<2>(color));

        materialColors.apply_color();

        glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer[0]);
        glVertexPointer(3, GL_FLOAT, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer[1]);
        glNormalPointer(GL_FLOAT, 0, 0);

        if (!(this->texture_path.empty())) { // Has a texture
            glBindTexture(GL_TEXTURE_2D, this->tex_id);
            glBindBuffer(GL_ARRAY_BUFFER, this->model_tex_id);
            glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
        }

        glDrawArrays(GL_TRIANGLES, 0, (int) n_triangles);

        glBindTexture(GL_TEXTURE_2D, 0); // Resetting the texture
    }

    Model::Model(const char *path, const string &texture_path, const MaterialColors materialColor) : Model(path) {
        this->texture_path = texture_path;
        if (!(this->texture_path.empty())) loadTexture();

        this->materialColors = materialColor;
    }

    void Model::loadTexture() {
        if (model_ids.count(this->texture_path) == 0) {

            unsigned int t, tw, th;
            unsigned char *texData;

            ilInit();
            ilEnable(IL_ORIGIN_SET);
            ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
            ilGenImages(1, &t);
            ilBindImage(t);
            if (!ilLoadImage((ILstring) texture_path.c_str())) {
                cerr << "\'" << texture_path << "\'" << " path texture image is invalid!" << endl;
                exit(1);
            }

            tw = ilGetInteger(IL_IMAGE_WIDTH);
            th = ilGetInteger(IL_IMAGE_HEIGHT);
            ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
            texData = ilGetData();

            glGenTextures(1, &tex_id);

            glBindTexture(GL_TEXTURE_2D, tex_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (signed) tw, (signed) th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);

        } else {
            this->tex_id = texture_ids[this->texture_path];
        }
    }

    vector<float> Model::parseTextureCoordinates(char *path) {
        vector<float> tex_points;

        tuple<float, float> point1;
        tuple<float, float> point2;
        tuple<float, float> point3;

        FILE *f = fopen(path, "r");

        if (!f) {
            cerr << "\"" << path << "\" path to texture coordinates is invalid!" << endl;
            return {};
        }

        // Reading the .text file
        while (fscanf(f, "(%f,%f);(%f,%f);(%f,%f)\n",

                      &get<0>(point1), &get<1>(point1),
                      &get<0>(point2), &get<1>(point2),
                      &get<0>(point3), &get<1>(point3)) != EOF) {

            tex_points.push_back(get<0>(point1));
            tex_points.push_back(get<1>(point1));

            tex_points.push_back(get<0>(point2));
            tex_points.push_back(get<1>(point2));

            tex_points.push_back(get<0>(point3));
            tex_points.push_back(get<1>(point3));
        }
        return tex_points;
    }
}
