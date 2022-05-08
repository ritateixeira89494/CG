#ifndef __MODEL_H__
#define __MODEL_H__

#include "triangle.h"
#include "model/LightingColors.h"
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
            static map<string, pair<unsigned int, long>> model_ids;

            /// Number of triangles in the model
            long n_triangles;
            /// List of triangles
            unsigned int vbo_buffer = 0;

            string texture_path;

            LightingColors lightingColors;

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
            Model(const char *path, const string &texture_path, LightingColors color);

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
             * @brief Get the triangle list
             *
             * @return vector<float> Vertex array of the model
             */
            vector<float> get_triangles();


            /**
             * @brief Renders a model.
             *
             * @param cam_mode bool telling if camera mode is active or not 
             */
            void render(bool cam_mode);
    };
}

#endif // __MODEL_H__
