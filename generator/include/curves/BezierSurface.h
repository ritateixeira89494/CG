#ifndef CG2022_BEZIERSURFACE_H
#define CG2022_BEZIERSURFACE_H

#include <tuple>
#include "utils/Matrix.h"

class BezierSurface {
    private:
        /**
         * Calculates all points of a bezier surface and it's normal with a given tessellation value.
         * @param control_points the control points of the patch.
         * @param tessellation the tessellation level.
         * @return tuple with all points and all normal vectors of the bezier surface.
         */
        static std::tuple<std::vector<std::vector<tuple<float, float, float>>>, std::vector<std::vector<tuple<float, float, float>>>>
        get_all_points_bezier_surface(vector<vector<tuple<float, float, float> *>> control_points, int tessellation);

        /**
         * Calculates a bezier surface's point and it's normal in a given time.
         *
         * @param pre_cal_x pre-calculated matrix of the x coordinates control points (M * Points_x * M).
         * @param pre_cal_y pre-calculated matrix of the y coordinates control points (M * Points_y * M).
         * @param pre_cal_z pre-calculated matrix of the z coordinates control points (M * Points_z * M).
         * @param u time value of the vertical curve.
         * @param v u time value of the horizontal curve.
         * @return tuple with point of the surface and it's normal in a given time.
         */
        static std::tuple<std::tuple<float, float, float>, std::tuple<float, float, float>>
        P(Matrix *pre_cal_x, Matrix *pre_cal_y, Matrix *pre_cal_z, float u, float v);

        /**
         * Calculates the normal vector in a specific point
         *
         * @param pre_cal_x pre-calculated matrix of the x coordinates control points (M * Points_x * M).
         * @param pre_cal_y pre-calculated matrix of the y coordinates control points (M * Points_y * M).
         * @param pre_cal_z pre-calculated matrix of the z coordinates control points (M * Points_z * M).
         * @param u time value of the vertical curve.
         * @param v u time value of the horizontal curve.
         * @return normal vector of the surface at the specified point
         */
        static std::tuple<float, float, float>
        get_normal(Matrix *pre_cal_x, Matrix *pre_cal_y, Matrix *pre_cal_z, const float u, const float v);

        /**
         * Generates and appends all triangles to a given file name.
         *
         * @param points the points of the patch.
         * @param file_path a file path.
         */
        static void generate_triangles(std::vector<std::vector<tuple<float, float, float>>> points,
                                       const char *file_path);

    public:
        /**
         * Process a file of bezier patches.
         * Creates the points of the patch and writes the triangles to the output_file argument.
         *
         * @param file_path a file path.
         * @param output_file a output file path.
         * @param tessellation the tessellation level.
         */
        static void processBezierPatches(char *file_path, char *output_file, int tessellation);
};


#endif //CG2022_BEZIERSURFACE_H
