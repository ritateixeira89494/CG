#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

#include "curves/BezierSurface.h"
#include <tuple>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include "utils/Matrix.h"

/**
 * Bezier Matrix
 * Matrix used to defined the Bezier curve.
 */
std::vector<std::vector<float>> bezier_matrix = {
        {-1, 3,  -3, 1},
        {3,  -6, 3,  0},
        {-3, 3,  0,  0},
        {1,  0,  0,  0}
};

/**
 * Converting the Bezier matrix to a Matrix object.
 */
static Matrix M = Matrix(bezier_matrix);

std::tuple<float, float, float>
BezierSurface::P(Matrix *pre_cal_x, Matrix *pre_cal_y, Matrix *pre_cal_z, const float u, const float v) {
    // [u^3, u^2, u, 1]
    Matrix u_vector = Matrix({
                                     {powf(u, 3), powf(u, 2), u, 1}
                             });

    // [v^3, v^2, v, 1]
    Matrix v_vector = Matrix({
                                     {powf(v, 3)},
                                     {powf(v, 2)},
                                     {v},
                                     {1}
                             });

    Matrix res_x = u_vector * *pre_cal_x * v_vector; // u * M * P_x * M * v
    Matrix res_y = u_vector * *pre_cal_y * v_vector; // u * M * P_y * M * v
    Matrix res_z = u_vector * *pre_cal_z * v_vector; // u * M * P_z * M * v

    // Getting the scalar of the matrix.
    float x = res_x.get_matrix()[0][0];
    float y = res_y.get_matrix()[0][0];
    float z = res_z.get_matrix()[0][0];

    return {x, y, z};
}

std::vector<std::vector<tuple<float, float, float>>>
BezierSurface::get_all_points_bezier_surface(vector<vector<tuple<float, float, float> *>> control_points,
                                             int tessellation) {
    if (tessellation <= 1) { // Check if the tessellation value is valid.
        cerr << "Tessellation value is invalid." << endl;
        exit(1);
    }

    // Separates the Matrix of vectors into a matrix of each coordinate.
    vector<vector<float>> p_vector_x(4, vector<float>(4, 0));
    vector<vector<float>> p_vector_y(4, vector<float>(4, 0));
    vector<vector<float>> p_vector_z(4, vector<float>(4, 0));
    for (int l = 0; l < 4; l++) {
        for (int col = 0; col < 4; col++) {
            p_vector_x[l][col] = get<0>(*control_points[l][col]);
            p_vector_y[l][col] = get<1>(*control_points[l][col]);
            p_vector_z[l][col] = get<2>(*control_points[l][col]);
        }
    }

    // Pre-calculus of matrix
    Matrix pre_cal_x = M * p_vector_x * M;
    Matrix pre_cal_y = M * p_vector_y * M;
    Matrix pre_cal_z = M * p_vector_z * M;

    std::vector<std::vector<tuple<float, float, float>>> res;

    // Finally, calculates the surface points
    for (int i = 0; i < tessellation; i++) {
        const float t_i = ((float) i) / ((float) tessellation - 1);
        res.emplace_back();
        for (int j = 0; j < tessellation; j++) {
            const float t_j = ((float) j) / ((float) tessellation - 1);
            auto p = BezierSurface::P(&pre_cal_x, &pre_cal_y, &pre_cal_z, t_i, t_j);
            res[i].push_back(p);
        }
    }

    return res;
}

void
BezierSurface::generate_triangles(std::vector<std::vector<tuple<float, float, float>>> points, const char *file_path) {
    ofstream file;
    file.open(file_path, std::ios_base::app);

    for (int i = 0; i < points.size() - 1; i++) {
        for (int o = 0; o < points[0].size() - 1; o++) {
            file << "(" << get<0>(points[i + 1][o]) << ", " << get<1>(points[i + 1][o]) << ", "
                 << get<2>(points[i + 1][o]) << ");";
            file << "(" << get<0>(points[i][o]) << ", " << get<1>(points[i][o]) << ", " << get<2>(points[i][o]) << ");";
            file << "(" << get<0>(points[i][o + 1]) << ", " << get<1>(points[i][o + 1]) << ", "
                 << get<2>(points[i][o + 1]) << ")" << endl;

            file << "(" << get<0>(points[i + 1][o + 1]) << ", " << get<1>(points[i + 1][o + 1]) << ", "
                 << get<2>(points[i + 1][o + 1]) << ");";
            file << "(" << get<0>(points[i + 1][o]) << ", " << get<1>(points[i + 1][o]) << ", "
                 << get<2>(points[i + 1][o]) << ");";
            file << "(" << get<0>(points[i][o + 1]) << ", " << get<1>(points[i][o + 1]) << ", "
                 << get<2>(points[i][o + 1]) << ")" << endl;
        }
    }

    file.close();
}

void BezierSurface::processBezierPatches(char *file_path, char *output_file, int tessellation) {
    int n_patches, n_cont_points;
    vector<int *> patches = {}; // Structure to store the patches indexes
    vector<tuple<float, float, float> *> control_points = {};


    FILE *f = fopen(file_path, "r");

    if (!f) {
        cerr << "Invalid bezier patch file path!" << endl;
        exit(1);
    }

    // Reset output file
    remove(output_file);

    fscanf(f, "%d", &n_patches);

    for (int i = 0; i < n_patches; i++) {
        int *patch = (int *) malloc(sizeof(int) * 16);
        fscanf(f, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &patch[0], &patch[1], &patch[2],
               &patch[3], &patch[4],
               &patch[5], &patch[6], &patch[7], &patch[8], &patch[9], &patch[10], &patch[11], &patch[12], &patch[13],
               &patch[14], &patch[15]);
        patches.push_back(patch);
    }

    fscanf(f, "%d", &n_cont_points);

    for (int i = 0; i < n_cont_points; i++) {
        auto xyz = new tuple<float, float, float>;
        fscanf(f, "%f, %f, %f", &(get<0>(*xyz)), &(get<1>(*xyz)), &(get<2>(*xyz)));
        control_points.push_back(xyz);
    }

    for (const int *patch: patches) {
        vector<vector<tuple<float, float, float> *>> c_p_patch; // Control Points of the patch

        for (int i = 0; i < 4; i++) {
            c_p_patch.emplace_back();
            for (int o = 0; o < 4; o++) {
                c_p_patch[i].push_back(control_points[patch[(i * 4 + o)]]);
            }
        }

        auto points = BezierSurface::get_all_points_bezier_surface(c_p_patch, tessellation);
        BezierSurface::generate_triangles(points, output_file);
    }

    // Free everything
    for (auto point: control_points) free(point);
    for (auto patch: patches) free(patch);
}

#pragma clang diagnostic pop