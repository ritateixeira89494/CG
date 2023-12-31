#ifndef __MODEL_H__
#define __MODEL_H__

#include "triangle.h"
#include "model/MaterialColors.h"
#include <vector>
#include <string>
#include <map>

using namespace std;
using namespace triangle;

namespace model {
    class Model {
        private:
            /**
             * Map to store the ids of the vbo that is going to be storing the model in the GPU.
             */
            static map<string, tuple<unsigned int, long, unsigned int>> model_ids;

            /**
             * Map to store the ids of the vbo that is going to be storing the normals in the GPU.
             */
            static map<string, pair<unsigned int, long>> normal_ids;

            /**
             * Map to store the already loaded image textures.
             */
            static map<string, unsigned int> texture_ids;

            /// Number of triangles in the model
            long n_triangles;

            /// List of triangles
            unsigned int vbo_buffer[2] = { 0,0 };

            // Id of the texture model coordenates
            unsigned int model_tex_id = 0;

            // Id of the texture image
            unsigned int tex_id = 0;

            string texture_path;

            MaterialColors materialColors;

            tuple<float, float, float> color;

        public:
            /// Initializes an empty model

            Model();

            /**
             * @brief Initializes and loads a ".3d" model
             *
             * @param path File path
             */
            explicit Model(const char *path);

            /**
             * @brief Initializes and loads a "3d" model with color.
             *
             * @param path File path
             *
             * @param path
             * @param color
             */
            Model(const char *path, tuple<float, float, float> color);


            /*
             * // TODO: Document this constructor
             */
            Model(const char *path, const string &texture_path, MaterialColors color);

            /**
             * @brief Get the number of triangles
             *
             * @return int number of triangles
             */
            long get_n_triangles() const;

            /**
             * @brief Loads a model from a ".3d" file
             *
             * @param path File path
             * @return Number of triangles loaded
             */
            long load_model(char *path); // Loads the model from a ".3d" file

            /**
             * @brief Loads a texture from a image.
             * @return
             */
            void loadTexture();

            /**
             * @brief Loads a model from a ".normal" file
             *
             * @param path File path
             * @return Number of normals loaded
             */
            long load_normal(char *path); // Loads the model from a ".normal" file
            /**
             * @brief Get the triangle list
             *
             * @return vector<float> Vertex array of the model
             */
            vector<float> get_triangles();

            /**
             * @brief Set the Color of the object
             *
             * @param lc MaterialColors object to set
             */
            void set_material_colors(MaterialColors lc);

            /**
             * @brief Renders a model.
             *
             * @param cam_mode bool telling if camera mode is active or not 
             */
            void render(bool cam_mode);


            vector<float> parseTextureCoordinates(char *path);
    };
}

#endif // __MODEL_H__
