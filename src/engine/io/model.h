#ifndef __IO_H__
#define __IO_H__

#include <GL/glut.h>
#include <cstdint>

namespace model {
    class Model {
        private:
            int n_triangles;
            GLfloat *points;
        public:
            void init();
            int get_n_triangles();
            int load_model(char *path);
    };
}

#endif // __IO_H__
