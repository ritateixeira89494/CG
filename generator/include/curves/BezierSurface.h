#ifndef CG2022_BEZIERSURFACE_H
#define CG2022_BEZIERSURFACE_H

#include <tuple>
#include "utils/Matrix.h"

class BezierSurface {
    public:
        static std::tuple<float, float, float> P(Matrix *pre_cal_control_points, float u, float v);
};


#endif //CG2022_BEZIERSURFACE_H
