#include "model/Color.h"

Color::Color() { // Default values for the color
    diffuse = make_tuple(200, 200, 200);
    ambient = make_tuple(50, 50, 50);
    specular = make_tuple(0, 0, 0);
    emissive = make_tuple(0, 0, 0);
    shininess = 0;
}

Color::Color(const tuple<float, float, float> &diffuse, const tuple<float, float, float> &ambient,
             const tuple<float, float, float> &specular, const tuple<float, float, float> &emissive, float shininess)
        : diffuse(diffuse), ambient(ambient), specular(specular), emissive(emissive), shininess(shininess) {}
