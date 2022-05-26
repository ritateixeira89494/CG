#include "lighting/Light.h"
#include <iterator>
#include <GL/gl.h>

using namespace std;  
  
namespace lighting { 
    
    int Light::n_lights = 0;

    Light::Light() {
        this->id = n_lights;
        n_lights++;

        glEnable(GL_LIGHT0 + id);

        glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0 + id, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular);
    }

    Light::Light(float diffuse[4], float ambient[4], float specular[4]) {
        this->id = n_lights;
        n_lights++;

        for(int i = 0; i < 4; i++) {
            this->diffuse[i] = diffuse[i];
            this->ambient[i] = ambient[i];
            this->specular[i] = specular[i];
        }

        glEnable(GL_LIGHT0 + id);

        glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0 + id, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular);
    }
}
