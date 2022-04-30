#include "curves/BezierSurface.h"
#include <tuple>
#include <cmath>
#include <vector>
#include <iostream>
#include "utils/Matrix.h"

std::vector<std::vector<float>> bezier_matrix = {
        {-1, 3,  -3, 1},
        {3,  -6, 3,  0},
        {-3, 3,  0,  0},
        {1,  0,  0,  0}
};

Matrix M = Matrix(bezier_matrix);

std::tuple<float, float, float>
BezierSurface::P(Matrix *pre_cal_x, Matrix *pre_cal_y, Matrix *pre_cal_z, const float u, const float v) {
    Matrix u_vector = Matrix({
                                     {powf(u, 3), powf(u, 2), u, 1}
                             });

    Matrix v_vector = Matrix({
                                     {powf(v, 3)},
                                     {powf(v, 2)},
                                     {v},
                                     {1}
                             });

    Matrix res_x = u_vector * *pre_cal_x * v_vector;
    Matrix res_y = u_vector * *pre_cal_y * v_vector;
    Matrix res_z = u_vector * *pre_cal_z * v_vector;

    float x = res_x.get_matrix()[0][0];
    float y = res_y.get_matrix()[0][0];
    float z = res_z.get_matrix()[0][0];

    return {x, y, z};
}

// TODO: Pre-calculate M * points * M.transpose() // Why transpose? Since M is symmetric?

std::vector<std::vector<tuple<float, float, float>>>
BezierSurface::get_all_points_bezier_surface(vector<vector<tuple<float, float, float>>> control_points,
                                             int tessellation) {
    if (tessellation <= 1) {
        cerr << "Tessellation value is invalid." << endl;
        exit(1);
    }
    cout << "[Bezier Surface] Number of points: " << tessellation << endl;

    vector<vector<float>> p_vector_x(4, vector<float>(4, 0));
    vector<vector<float>> p_vector_y(4, vector<float>(4, 0));
    vector<vector<float>> p_vector_z(4, vector<float>(4, 0));
    for (int l = 0; l < 4; l++) {
        for (int col = 0; col < 4; col++) {
            p_vector_x[l][col] = get<0>(control_points[l][col]);
            p_vector_y[l][col] = get<1>(control_points[l][col]);
            p_vector_z[l][col] = get<2>(control_points[l][col]);
        }
    }

    //std::cout << "p_vector_x: " << endl;

    // Pre-calculus of matrix
    Matrix pre_cal_x = M * p_vector_x * M.transpose();
    Matrix pre_cal_y = M * p_vector_y * M.transpose();
    Matrix pre_cal_z = M * p_vector_z * M.transpose();

    std::vector<std::vector<tuple<float, float, float>>> res;

    for (int i = 0; i < tessellation; i++) {
        const float t_i = ((float) i) / ((float) tessellation - 1);
        res.push_back({});
        for (int j = 0; j < tessellation; j++) {
            const float t_j = ((float) j) / ((float) tessellation - 1);
            auto p = BezierSurface::P(&pre_cal_x, &pre_cal_y, &pre_cal_z, t_i, t_j);
            res[i].push_back(p);
            cout << "t_i=" << t_i << " t_j=" << t_j << " point=[" << "x=" << get<0>(p) << " y=" << get<1>(p) << " z="
                 << get<2>(p) << "]" << endl;
        }
    }

    return res;
}

void
BezierSurface::generate_triangles(std::vector<std::vector<tuple<float, float, float>>> points, const char *file_name) {
    ofstream file;
    file.open(file_name);

    for (int i = 0; i < points.size() - 1; i++) {
        for (int o = 0; o < points[0].size() - 1; o++) {
            file << "(" << get<0>(points[i][o]) << ", " << get<1>(points[i][o]) << ", " << get<2>(points[i][o]) << ");";
            file << "(" << get<0>(points[i + 1][o]) << ", " << get<1>(points[i + 1][o]) << ", "
                 << get<2>(points[i + 1][o]) << ");";
            file << "(" << get<0>(points[i][o + 1]) << ", " << get<1>(points[i][o + 1]) << ", "
                 << get<2>(points[i][o + 1]) << ")" << endl;

            file << "(" << get<0>(points[i + 1][o]) << ", " << get<1>(points[i + 1][o]) << ", "
                 << get<2>(points[i + 1][o]) << ");";
            file << "(" << get<0>(points[i + 1][o + 1]) << ", " << get<1>(points[i + 1][o + 1]) << ", "
                 << get<2>(points[i + 1][o + 1]) << ");";
            file << "(" << get<0>(points[i][o + 1]) << ", " << get<1>(points[i][o + 1]) << ", "
                 << get<2>(points[i][o + 1]) << ")" << endl;
        }
    }

    file.close();
}
