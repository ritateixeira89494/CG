#ifndef __MODEL_H__
#define __MODEL_H__

#include "triangle.h"
#include "model/Color.h"
#include <vector>

using namespace std;
using namespace triangle;

namespace model {
    class Model {
        private:
            /// Number of triangles in the model
            int n_triangles;
            /// List of triangles
            vector<Triangle> triangles;

            string texture_path;

            Color color;

        public:
            /// Initializes an empty model

            Model();

            /**
             * @brief Initializes and loads a ".3d" model
             *
             * @param path File path
             */
            explicit Model(const char *path);

            Model(const char *path, const string &texture_path, const Color color);

            /**
             * @brief Get the number of triangles
             *
             * @return int number of triangles
             */
            int get_n_triangles();

            /**
             * @brief Loads a model from a ".3d" file
             *
             * @param path File path
             * @return int Number of triangles loaded
             */
            int load_model(char *path); // Loads the model from a ".3d" file
            /**
             * @brief Get the triangle list
             *
             * @return vector<Triangle *> List of triangles of the model
             */
            vector<Triangle> get_triangles();


            /**
             * @brief Renders a model.
             *
             */
            void render();
    };
}

#endif // __MODEL_H__
