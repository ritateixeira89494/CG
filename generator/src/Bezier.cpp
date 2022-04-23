#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

void drawBezierPatches(char *file) {
    int n_patches, n_pontos_controlo;
    vector<int *> patches = {}; // Structure to store the patches indexes
    vector<float *> controlPoints = {};


    FILE *f = fopen(file, "r");

    fscanf(f, "%d", &n_patches);

    for (int i = 0; i < n_patches; i++) {
        int *patch = (int *) malloc(sizeof(int) * 16);
        fscanf(f, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &patch[0], &patch[1], &patch[2],
               &patch[3], &patch[4],
               &patch[5], &patch[6], &patch[7], &patch[8], &patch[9], &patch[10], &patch[11], &patch[12], &patch[13],
               &patch[14], &patch[15]);
        patches.push_back(patch);
    }

    fscanf(f, "%d", &n_pontos_controlo);

    for (int i = 0; i < n_pontos_controlo; i++) {
        float *xyz = (float *) malloc(sizeof(float) * 3);
        fscanf(f, "%f, %f, %f", &xyz[0], &xyz[1], &xyz[2]);
        controlPoints.push_back(xyz);
    }

    // Print stuff
    for (const int *patch: patches) {
        for (int i = 0; i < 16; i++) {
            cout << patch[i] << " ";
        }
        cout << endl;
    }

    for (const float *xyz: controlPoints) {
        cout << "x=" << xyz[0] << " y=" << xyz[1] << " z=" << xyz[2] << endl;
    }


}