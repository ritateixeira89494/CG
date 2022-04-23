#include <math.h>

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include <stdio.h>

#include "curves/Bezier.h"

using namespace std;

int main(int argc, char **argv) {
    char filePath[] = "teapot.patch";
    drawBezierPatches(filePath);
    return 0;
}

