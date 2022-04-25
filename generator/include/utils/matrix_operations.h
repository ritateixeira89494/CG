#ifndef CG2022_MATRIX_OPERATIONS_H
#define CG2022_MATRIX_OPERATIONS_H

void cross(float *a, float *b, float *res);

void normalize(float *a);

float length(float *v);

void multMatrixVector(const float *m, const float *v, float *res);

#endif //CG2022_MATRIX_OPERATIONS_H
