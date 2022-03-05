#include <GL/gl.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

#include "GL/glut.h"
#include "model.h"


namespace model {
    int Model::get_n_triangles() {
        return n_triangles;
    }

    int Model::load_model(char *path) {
        FILE *f = fopen(path, "r");
        if(!f){
            return -1;
        }

        int triangs = 0;
        fscanf(f, "%d\n", &triangs);

        points = (GLfloat *) malloc(3*triangs*sizeof(GLfloat));

        int mem = triangs * 9;
        for(int i = 0; i < mem; i+=9) {
            fscanf(f, "(%f,%f,%f);(%f,%f,%f);(%f,%f,%f)\n", &points[i+0], &points[i+1], &points[i+2],
                                                            &points[i+3], &points[i+4], &points[i+5],
                                                            &points[i+6], &points[i+7], &points[i+8]
            );
        }

        n_triangles = triangs;

        return 0;
    }

    void Model::init() {
        n_triangles = 0;
        points = NULL;
    }
}
