#include <math.h>
#include "main.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include <stdio.h>

#include "../include/Bezier.h"

using namespace std;

int main(int argc, char **argv) {
    char filePath[] = "../engine/test/teapot.patch";
    drawBezierPatches(filePath);
    return 0;
}

