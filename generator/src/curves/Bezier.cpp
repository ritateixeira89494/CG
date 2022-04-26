#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

#include <cstdio>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES

#include <math.h>
#include "utils/matrix_operations.h"

using namespace std;

/*
 * De maneira a construir a superfície utilizando as curvas de Bezier, iremos receber um ficheiro do tipo _.patch_
 * Patch -> generator -> lista de triângulos -> engine
 * 1ª linha -> nº patches ( sscanf("%d", &patches); )
 * usar for para percorrer as linhas que contêm os 16 índices para cada patch -> armazenar em Arraylist
 * Nº de pontos de controlo ( sscanf("%d", &pontosControlo); )
 * usar for para percorrer cada linha com os (x, y, z) de cada ponto de controlo
 * wd
 *
 */

float bezier__matrix[4][4] = {
        {-1, 3,  -3, 1},
        {3,  -6, 3,  0},
        {-3, 3,  0,  0},
        {1,  0,  0,  0}
};

float p_0[3] = {0.f, 0.f, 0.f};
float p_1[3] = {0.f, 1.f, 0.f};
float p_2[3] = {1.f, 0.f, 0.f};
float p_3[3] = {1.f, 1.f, 0.f};


float P[3];

int tessellation = 4;

float **initialize_A(float *p0, float *p1, float *p2, float *p3) {
    auto **A = (float **) (calloc(4, sizeof(float *)));
    for (int i = 0; i < 4; i++) {
        A[i] = (float *) (calloc(4, sizeof(float)));
    }

    for (int i = 0; i < 3; i++) {
        float v[4] = {p0[i], p1[i], p2[i], p3[i]};
        multMatrixVector((float *) bezier__matrix, v, A[i]);
    }

    cout << "[Bezier] A matrix:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    return A;
}

/**
 *
 * @param t Time parameter. Has to variate between 0 (zero) and 1 (one).
 * @return Returns the point of the curve in the given time.
 */
float *p(float t, float **A) {
    float T[4] = {powf(t, 3), powf(t, 2), t, 1};

    // Multiplication between T vector and A matrix
    for (int i = 0; i < 3; i++) {
        P[i] = T[0] * A[i][0] + T[1] * A[i][1] + T[2] * A[i][2] + T[3] * A[i][3];
    }


    return nullptr; // TODO: Change return value.
    // TODO: Change return type to void since the return value is been written into the P global variable.
}

void get_bezier_point(float **A) {
    if (tessellation <= 1) {
        cerr << "Tessellation value is invalid." << endl;
        exit(1);
    }
    cout << "[Bezier] Number of points: " << tessellation << endl;

    for (int i = 0; i < tessellation; i++) {
        const float t = ((float) i) / ((float) tessellation - 1);
        p(t, A);
        cout << "t=" << t << " point=[" << "x=" << P[0] << " y=" << P[1] << " z=" << P[2] << "]" << endl;
    }
}

void getBezierTriangle() {
    // TODO: Code this function
}

void drawBezierPatches(char *file) {
    int n_patches, n_cont_points;
    vector<int *> patches = {}; // Structure to store the patches indexes
    vector<float *> control_points = {};


    FILE *f = fopen(file, "r");

    if (!f) {
        cerr << "Invalid bezier patch file path!" << endl;
        exit(1);
    }

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
        auto *xyz = (float *) malloc(sizeof(float) * 3);
        fscanf(f, "%f, %f, %f", &xyz[0], &xyz[1], &xyz[2]);
        control_points.push_back(xyz);
    }

    // Print stuff
    /*
    for (const int *patch: patches) {
        for (int i = 0; i < 16; i++) {
            cout << patch[i] << " ";
        }
        cout << endl;
    }

    for (const float *xyz: control_points) {
        cout << "x=" << xyz[0] << " y=" << xyz[1] << " z=" << xyz[2] << endl;
    }
     */

    float **A = initialize_A(p_0, p_1, p_2, p_3);
    get_bezier_point(A);
}

#pragma clang diagnostic pop