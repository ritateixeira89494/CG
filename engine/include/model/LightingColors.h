#ifndef CG2022_LIGHTINGCOLORS_H
#define CG2022_LIGHTINGCOLORS_H

#include <tuple>

using namespace std;

class LightingColors {
    public:
        // Types of colors
        tuple<float, float, float> diffuse;
        tuple<float, float, float> ambient;
        tuple<float, float, float> specular;
        tuple<float, float, float> emissive;
        float shininess;

        LightingColors();

        LightingColors(const tuple<float, float, float> &diffuse, const tuple<float, float, float> &ambient,
                       const tuple<float, float, float> &specular, const tuple<float, float, float> &emissive,
                       float shininess);
};


#endif //CG2022_LIGHTINGCOLORS_H
