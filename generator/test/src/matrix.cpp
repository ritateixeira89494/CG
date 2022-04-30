
#include <iostream>
#include "utils/Matrix.h"

using namespace std;

int main() {
    vector<vector<float> > v1 = {
            {-1, 3,  -3, 1},
            {3,  -6, 3,  0},
            {-3, 3,  0,  0},
            {1,  0,  0,  0}
    };

    vector<vector<float> > v2 = {
            {-1, 3,  -3, 1},
            {3,  -6, 3,  0},
            {-3, 3,  0,  0},
            {1,  0,  0,  0}
    };

    Matrix m1 = Matrix(v1);
    Matrix m2 = Matrix(v2);


    cout << "Sum of matrices" << endl;
    auto sum = ((m1 + m2)).get_matrix();
    for (const auto &line: sum) {
        for (auto elem: line) {
            cout << elem << " ";
        }
        cout << endl;
    }

    //

    cout << "Subtraction of matrices" << endl;
    auto sub = ((m1 - m2)).get_matrix();
    for (const auto &line: sub) {
        for (auto elem: line) {
            cout << elem << " ";
        }
        cout << endl;
    }

    //
    cout << "Multiplication " << endl;

    auto result = (m1 * m2).get_matrix();
    for (const auto &line: result) {
        for (auto elem: line) {
            cout << elem << " ";
        }
        cout << endl;
    }

    //
    cout << "Transpose of matrices" << endl;
    auto transp = m1.transpose().get_matrix();
    for (const auto &line: transp) {
        for (auto elem: line) {
            cout << elem << " ";
        }
        cout << endl;
    }
}