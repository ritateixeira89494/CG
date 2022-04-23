
#include <math.h>
#include "main.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include <stdio.h>

#include "Box.h"
#include "Sphere.h"
#include "Piramide.h"
#include "Plane.h"

using namespace std;

//Esta fun��o ir� ignorar uppercase e lowercase
bool iequals(const string &a, const string &b) {
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

/*
int main(int argc, char **argv) {
    if (iequals(argv[1], "Plane")) {
        float len = stoi(argv[2]);
        float div = stoi(argv[3]);
        drawPlane(len, div, argv[4]);
    } else if (iequals(argv[1], "Box")) {
        float units = stoi(argv[2]);
        float grid = stoi(argv[3]);
        drawBox(units, grid, argv[4]);
    } else if (iequals(argv[1], "Sphere")) {
        float radius = stoi(argv[2]);
        float slices = stoi(argv[3]);
        float stacks = stoi(argv[4]);
        drawSphere(radius, slices, stacks, argv[5]);
    } else if (iequals(argv[1], "Cone")) {
        float radius = stoi(argv[2]);
        float height = stoi(argv[3]);
        float slices = stoi(argv[4]);
        float stacks = stoi(argv[5]);
        drawPyramid(radius, height, slices, stacks, argv[6]);
    } else {
        cout << "Parâmetros incorretos";
    }

    return 1;
}

*/