#include "curves/BezierSurface.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    char filePath[] = "teapot.patch";

    tuple<float, float, float> P0 = {1, 5, -3};

    tuple<float, float, float> P1 = {-1, 3, 8};

    tuple<float, float, float> P2 = {0, 0, -3};

    tuple<float, float, float> P3 = {-1, 3, -3};

    tuple<float, float, float> P4 = {-1, 3, -3};

    tuple<float, float, float> P5 = {-1, 7, -3};

    tuple<float, float, float> P6 = {-1, 3, 9};

    tuple<float, float, float> P7 = {0, 3, 1};

    tuple<float, float, float> P8 = {-1, 1, 3};

    tuple<float, float, float> P9 = {5, 3, 3};

    tuple<float, float, float> P10 = {-1, 6, -3};

    tuple<float, float, float> P11 = {2, 2, -3};

    tuple<float, float, float> P12 = {4, 4, -3};

    tuple<float, float, float> P13 = {9, 7, -8};

    tuple<float, float, float> P14 = {-1, 1, -1};

    tuple<float, float, float> P15 = {-9, 1, -3};

    vector<vector<tuple<float, float, float>>> control_points = {
            {P0,  P1,  P2,  P3},
            {P4,  P5,  P6,  P7},
            {P8,  P9,  P10, P11},
            {P12, P13, P14, P15}
    };

    auto p = BezierSurface::get_all_points_bezier_surface(control_points, 50);

    cout << "----------" << endl;

    for (const auto &line: p) {
        for (auto elem: line) {
            cout << get<0>(elem) << " " << get<1>(elem) << " " << get<2>(elem) << " " << endl;
        }
        cout << endl;
    }

    BezierSurface::generate_triangles(p, "Rita.3d");

    return 0;
}
