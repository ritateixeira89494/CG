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
    map<string, tuple<unsigned int, long, unsigned int>> Model::model_ids = {}; // Path of the model -> (vbo_id, n_triangles, tex_id)

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
            glGenBuffers(1, &vbo_buffer); // Initialize vbo buffer
            glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer);
            glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (triangles.size() * sizeof(float)), triangles.data(),
                         GL_STATIC_DRAW);

            // Reading the .text file
            string str_path = string(path);
            auto t = parseTextureFile(
                    const_cast<char *>((str_path.substr(0, str_path.length() - 3) + ".text").c_str()));

            // Texture coordenates
            glGenBuffers(1, &model_tex_id);
            glBindBuffer(GL_ARRAY_BUFFER, model_tex_id);
            glBufferData(GL_ARRAY_BUFFER, (long) sizeof(float) * 2 * triangles.size(), t.data(), GL_STATIC_DRAW);

            model_ids.insert({str_path, {vbo_buffer, n_triangles, 0}});
        } else {
            vbo_buffer = get<0>(model_ids[str_path]);
            n_triangles = get<1>(model_ids[str_path]);
            model_tex_id = get<2>(model_ids[str_path]);
        }

        return n_triangles;
    }

    Model::Model() {
        n_triangles = 0;
        lightingColors = new LightingColors();
        texture_path = "";
    }

    Model::Model(const char *path) {
        n_triangles = 0;
        lightingColors = new LightingColors();
        texture_path = "";
        color = {1.0, 1.0, 1.0};
        load_model(const_cast<char *>(path));
    }

    Model::Model(const char *path, tuple<float, float, float> color) {
        n_triangles = 0;
        lightingColors = new LightingColors();
        texture_path = "";
        this->color = color;
        load_model(const_cast<char *>(path));
    }

    void Model::render(bool cam_mode) {
        if (!cam_mode)
            glColor3f(get<0>(color), get<1>(color), get<2>(color));

        glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer);
        glVertexPointer(3, GL_FLOAT, 0, nullptr);

        if (!(this->texture_path.empty())) {
            glBindTexture(GL_TEXTURE_2D, this->tex_id);
            glBindBuffer(GL_ARRAY_BUFFER, this->model_tex_id);
            glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
        }

        glDrawArrays(GL_TRIANGLES, 0, (int) n_triangles);

        glBindTexture(GL_TEXTURE_2D, 0); // Resetting the texture
    }


    void Model::loadTexture() {
        unsigned int t, tw, th;
        unsigned char *texData;

        ilInit();
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
        ilGenImages(1, &t);
        ilBindImage(t);
        ilLoadImage((ILstring) texture_path.c_str());
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
    }


    Model::Model(const char *path, char *texture_path, LightingColors *lightingColor) : Model(path) {
        this->texture_path = texture_path;
        // TODO: Loading the texture coordenate and rendering the texture

        this->lightingColors = lightingColor;
    }


    vector<tuple<float, float>> Model::parseTextureFile(char *path) {
        vector<tuple<float, float>> tex_points;

        tuple<float, float> point1;
        tuple<float, float> point2;
        tuple<float, float> point3;

        FILE *f = fopen(path, "r");

        // Reading the .text file
        while (fscanf(f, "(%f,%f);(%f,%f);(%f,%f)\n",

                      &get<0>(point1), &get<1>(point1),
                      &get<0>(point2), &get<1>(point2),
                      &get<0>(point3), &get<1>(point3)

        ) != EOF) {

            tex_points.push_back(point1);
            tex_points.push_back(point2);
            tex_points.push_back(point3);
        }
        return {};
    }
}
