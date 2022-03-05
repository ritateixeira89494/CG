#include "tinyxml2.h"
#include "io/model.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdio>

using namespace tinyxml2;
using namespace model;

int main(int argc, char *argv[]) {
    Model m;
    m.init();

    m.load_model((char *) "test.3d");

    printf("n_triangs = %d", m.get_n_triangles());
}
