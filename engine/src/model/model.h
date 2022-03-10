#ifndef __MODEL_H__
#define __MODEL_H__

#include "triangle.h"
#include <GL/glut.h>
#include <vector>

using namespace std;
using namespace triangle;

namespace model {
    class Model {
        private:
            int n_triangles;
            vector<Triangle *> triangles;
        public:
            Model();                    // Initializes an empty model
            explicit Model(const char *path);          // Initializes and loads a ".3d" model
            int get_n_triangles();      // Returns the number of triangles
            int load_model(char *path); // Loads the model from a ".3d" file
            vector<Triangle *> get_triangles();
    };
}

#endif // __IO_H__
