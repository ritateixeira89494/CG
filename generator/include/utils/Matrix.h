#ifndef CG2022_MATRIX_H
#define CG2022_MATRIX_H

#include <vector>
#include <ostream>

using namespace std; // TODO: Passar para std::vector;

class Matrix {
    private:
        vector<vector<float>> mat;

    public:
        /// Creates an empty matrix
        Matrix();

        /**
         * @brief Creates a matrix from a vector of vectors
         * @param matrix Matrix to create the matrix from
         */
        Matrix(vector<vector<float>> matrix);

        /**
         * Replace the current matrix with the provided one
         * @param matrix Matrix to replace with
         */
        void set_matrix(vector<vector<float>> matrix);

        /**
         * Returns the matrix as a vector of vectors
         * @return Vector of vectors
         */
        vector<vector<float>> get_matrix();

        /**
         * Returns the number of lines of the matrix
         * @return Number of lines
         */
        int get_lines();

        /**
         * Returns the number of columns of the matrix
         * @return Number of columns
         */
        int get_cols();

        /* Matrix Operations */

        // Matrix mathematical operations
        Matrix operator+(const Matrix matrix);

        Matrix *operator+=(const Matrix matrix);

        Matrix operator-(const Matrix matrix);

        Matrix *operator-=(const Matrix matrix);

        Matrix operator*(const Matrix matrix);

        Matrix *operator*=(const Matrix matrix);

        Matrix *transpose();

        std::ostream &operator<<(std::ostream &outs);
};


#endif //CG2022_MATRIX_H
