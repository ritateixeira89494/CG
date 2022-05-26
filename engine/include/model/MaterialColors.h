#ifndef CG2022_LIGHTINGCOLORS_H
#define CG2022_LIGHTINGCOLORS_H

#include <tuple>

using namespace std;

class MaterialColors {
    private:
        // Types of colors
        float diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        float ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
        float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        float emissive[4] = { 0.1f, 0.1f, 0.1f, 0.1f };

        /// Material's shininess
        int shininess = 128;
    public:
        MaterialColors() = default;

        MaterialColors(
                const int *diffuse, const int *ambient,
                const int *specular, const int *emissive,
                int shininess
        );

        void apply_color();
};


#endif //CG2022_LIGHTINGCOLORS_H
