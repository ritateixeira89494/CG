#ifndef CG2022_BEZIERSURFACE_H
#define CG2022_BEZIERSURFACE_H

#include <tuple>
#include "utils/Matrix.h"

class BezierSurface {
    public:
        static std::vector<std::vector<tuple<float, float, float>>>
        get_all_points_bezier_surface(vector<vector<tuple<float, float, float> *>> control_points, int tessellation);

        static std::tuple<float, float, float>
        P(Matrix *pre_cal_x, Matrix *pre_cal_y, Matrix *pre_cal_z, float u, float v);

        static void generate_triangles(std::vector<std::vector<tuple<float, float, float>>> points,
                                       const char *file_name);

        static void processBezierPatches(char *file, char *output_file, int tessellation);
};


#endif //CG2022_BEZIERSURFACE_H
