#include <GL/glut.h>
#include <iostream>

#include "io/model.h"

using namespace std;
using namespace model;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        clog << "Wrong number of arguments provided! Required 1" << endl;
        return -1;
    }
    
    Model m;
    
    char *path = argv[1];
    int err_code = m.load_model(path);
    if(err_code == -1) {
        clog << "File \"" << path << "\" not found!" << endl;
        return -2;
    }

    cout << "Number of triangles: " << m.get_n_triangles() << endl;

    return 0;
}
