#include <iostream>
#include "curves/BezierSurface.h"

using namespace std;

int main(int argc, char **argv) {
    char file_path[] = "teapot.patch";
    char output_file[] = "bezier.3d";
    auto tessellation = 5;

    BezierSurface::processBezierPatches(file_path, output_file, tessellation);

    std::cout << "3d file successfully generated!" << endl;

    return 0;
}
