
#ifndef DEBUG_MODE
#define DEBUG_MODE 1
#endif
#define DEBUG(x) {if(DEBUG_MODE) std::cerr << x;}


#include <math.h>

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include <stdio.h>

#include "primitives/Box.h"
#include "primitives/Sphere.h"
#include "primitives/Piramide.h"
#include "primitives/Plane.h"
#include "curves/BezierSurface.h"

using namespace std;

//Esta fun��o ir� ignorar uppercase e lowercase
bool iequals(const string &a, const string &b) {
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

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
    } else if (iequals(argv[1], "bezier")) { //  generator bezier teapot.patch 10 bezier.3d
        char *patch_file = argv[2];
        int tessellation = stoi(argv[3]);
        char *output_file = argv[4];
        BezierSurface::processBezierPatches(patch_file, output_file, tessellation);
    } else {
        cout << "Invalid arguments!";
    }

    return 0;
}