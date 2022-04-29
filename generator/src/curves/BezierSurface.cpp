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

tuple<float, float, float> P0 = {-1, 3, -3};

tuple<float, float, float> P1 = {-1, 3, -3};


tuple<float, float, float> P2 = {-1,
                                 3,
                                 -3};

tuple<float, float, float> P3 = {-1, 3, -3};

tuple<float, float, float> P4 = {-1, 3, -3};

tuple<float, float, float> P5 = {-1, 3, -3};

tuple<float, float, float> P6 = {-1, 3, -3};

tuple<float, float, float> P7 = {-1, 3, -3};

tuple<float, float, float> P8 = {-1, 3, -3};

tuple<float, float, float> P9 = {-1, 3, -3};

tuple<float, float, float> P10 = {-1, 3, -3};

tuple<float, float, float> P11 = {-1, 3, -3};

tuple<float, float, float> P12 = {-1, 3, -3};

tuple<float, float, float> P13 = {-1, 3, -3};

tuple<float, float, float> P14 = {-1, 3, -3};

tuple<float, float, float> P15 = {-1, 3, -3};


vector<vector<float>> p_vector_x = {
        {get<0>(P0),  get<0>(P1),  get<0>(P2),  get<0>(P3)},
        {get<0>(P4),  get<0>(P5),  get<0>(P6),  get<0>(P7)},
        {get<0>(P8),  get<0>(P9),  get<0>(P10), get<0>(P11)},
        {get<0>(P12), get<0>(P13), get<0>(P14), get<0>(P15)}
};

vector<vector<float>> p_vector_y = {
        {get<1>(P1),  get<1>(P1),  get<1>(P2),  get<1>(P3)},
        {get<1>(P4),  get<1>(P5),  get<1>(P6),  get<1>(P7)},
        {get<1>(P8),  get<1>(P9),  get<1>(P11), get<1>(P11)},
        {get<1>(P12), get<1>(P13), get<1>(P14), get<1>(P15)}
};

vector<vector<float>> p_vector_z = {
        {get<2>(P2),  get<2>(P1),  get<2>(P2),  get<2>(P3)},
        {get<2>(P4),  get<2>(P5),  get<2>(P6),  get<2>(P7)},
        {get<2>(P8),  get<2>(P9),  get<2>(P12), get<2>(P11)},
        {get<2>(P12), get<2>(P13), get<2>(P14), get<2>(P15)}
};

Matrix points = Matrix(p_vector_x);

//Matrix pre_calc_x = M * p_vector_x * M.transpose();

// TODO: Pre-calculate M * points * M.transpose() // Why transpose? Since M is symmetric?

std::tuple<float, float, float> BezierSurface::P(Matrix *control_points, float u, float v) {
    //control_points = &pre_calc_x;
    Matrix u_vector = Matrix({
                                     {powf(u, 3), powf(u, 2), u, 1}
                             });

    Matrix v_vector = Matrix({
                                     {powf(v, 3)},
                                     {powf(v, 2)},
                                     {v},
                                     {1}
                             });
    Matrix res_x = u_vector * M * p_vector_x * M.transpose() * v_vector;
    Matrix res_y = u_vector * M * p_vector_y * M.transpose() * v_vector;
    Matrix res_z = u_vector * M * p_vector_z * M.transpose() * v_vector;

    cout << "X: " << endl;
    res_x.print();
    cout << "Y: " << endl;
    res_y.print();
    cout << "Z: " << endl;
    res_z.print();

    return {1.f, 1.f, 1.f};
}