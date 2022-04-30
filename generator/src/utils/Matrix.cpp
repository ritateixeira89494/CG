#include "utils/Matrix.h"

#include "vector"
#include <iostream>

using namespace std;

Matrix::Matrix() {
    this->mat = {};
}

Matrix::Matrix(vector<vector<float>> matrix) {
    this->mat = matrix;
}

int Matrix::get_lines() {
    return mat.size();
}

int Matrix::get_cols() {
    return mat[0].size();
}

void Matrix::set_matrix(vector<vector<float>> matrix) {
    mat = matrix;
}

vector<vector<float>> Matrix::get_matrix() {
    return mat;
}

Matrix Matrix::operator+(Matrix matrix) {
    int this_lines = get_lines();
    int this_cols = get_cols();

    int their_lines = matrix.get_lines();
    int their_cols = matrix.get_cols();

    if (this_lines != their_lines || this_cols != their_cols) {
        cerr << "Matrix sizes are different!!! (" << this_lines << ", " << this_cols << ") | (" << their_lines << ", "
             << their_cols << ")" << endl;
        throw exception();
    }

    vector<vector<float>> v = {};
    auto this_matrix = get_matrix();
    auto their_matrix = matrix.get_matrix();

    for (int i = 0; i < this_lines; i++) {
        vector<float> new_line = {};
        for (int k = 0; k < this_cols; k++) {
            float val = this_matrix[i][k] + their_matrix[i][k];
            new_line.emplace_back(val);
        }
        v.emplace_back(new_line);
    }

    return Matrix(v);
}

Matrix *Matrix::operator+=(Matrix matrix) {
    Matrix m = this->operator+(matrix);
    this->mat = m.mat;

    return this;
}

Matrix Matrix::operator-(Matrix matrix) {
    int this_lines = get_lines();
    int this_cols = get_cols();

    int their_lines = matrix.get_lines();
    int their_cols = matrix.get_cols();

    if (this_lines != their_lines || this_cols != their_cols) {
        cerr << "Matrix sizes are different!!! (" << this_lines << ", " << this_cols << ") | (" << their_lines << ", "
             << their_cols << ")" << endl;
        throw exception();
    }

    vector<vector<float>> v = {};
    auto this_matrix = get_matrix();
    auto their_matrix = matrix.get_matrix();

    for (int i = 0; i < this_lines; i++) {
        vector<float> new_line = {};
        for (int k = 0; k < this_cols; k++) {
            float val = this_matrix[i][k] - their_matrix[i][k];
            new_line.emplace_back(val);
        }
        v.emplace_back(new_line);
    }

    return Matrix(v);
}

Matrix *Matrix::operator-=(Matrix matrix) {
    Matrix m = this->operator-(matrix);
    this->mat = m.mat;


    return this;
}

Matrix Matrix::operator*(Matrix matrix) {
// Getting the dimensions of the matrices
    int n1 = this->get_lines();
    int m1 = this->get_cols();

    int n2 = matrix.get_lines();
    int m2 = matrix.get_cols();


    if (m1 != n2) {
        cerr << "Invalid matrix dimensions! Can't multiply a matrix with " << n1 << "x" << m1 << " with " << n2 << "x"
             << m2 << endl;
        exit(1);
    }

    //cout << "Dimension of the result matrix: " << n1 << "x" << m2 << endl;

    vector<vector<float>> v(n1, vector<float>(m2, 0));

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            for (int k = 0; k < n2; k++) {
                v[i][j] += this->mat[i][k] * matrix.mat[k][j];
            }
        }
    }

    return v;
}

Matrix *Matrix::operator*=(const Matrix matrix) {
    Matrix m = this->operator*(matrix);
    this->mat = m.mat;


    return this;
}

Matrix Matrix::transpose() {
    int lines = get_lines();
    int cols = get_cols();
    vector<vector<float>> new_matrix = {};
    for (int i = 0; i < cols; i++) {
        vector<float> new_line = {};
        for (int k = 0; k < lines; k++) {
            new_line.emplace_back(this->mat[k][i]);
        }
        new_matrix.emplace_back(new_line);
    }

    return Matrix(new_matrix);
}

ostream &operator<<(ostream &outs, Matrix m) {
    outs << "lines: " << m.get_lines() << " | cols: " << m.get_cols();

    for (vector<float> line: m.get_matrix()) {
        outs << "[ ";
        for (float val: line) {
            outs << val << ", ";
        }
        outs << "] " << endl;
    }

    return outs;
}

void Matrix::print() {
    auto m = this->get_matrix();
    for (auto line: m) {
        for (auto elem: line) {
            cout << elem << " ";
        }
        cout << endl;
    }
}
