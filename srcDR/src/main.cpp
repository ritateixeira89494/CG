
#include <math.h>
#include "main.h"
#include "point.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include "Box.cpp"
#include "Sphere.cpp"
#include "Piramide.cpp"

using namespace std;

int sizeSquare = 1;
int divisions = 8;

//Camara
float posX = 5;
float posY = 5;
float posZ = 5;

float alpha = 0.7;
float beta = 0.7;
float radiusCamera = 30;


// Desenha um plano a partir dos pontos individuais.
// De cada ponto, sabe-se o lado de cada quadrado, logo � f�cil desenhar o resto do quadrado.
void drawPlaneXY(float length, float divisions) {
    float increment = length / divisions;
    printf("Increment original %f", increment);
    //Draw base and top
    for (float line = 0; line < length; line = line + increment) {
        for (float collumn = 0; collumn < length; collumn = collumn + increment) {
            drawSquareXY(line, collumn, increment);
            drawSquareXY(line, collumn, increment, length);
            printf("Um quadrado %f", increment);
        }
    }
}

// Desenha um plano a partir dos pontos individuais.
// De cada ponto, sabe-se o lado de cada quadrado, logo � f�cil desenhar o resto do quadrado.
void drawPlaneYZ(float length, float divisions) {
    float increment = length / divisions;
    //Draw base and top
    for (float line = 0; line < length; line = line + increment) {
        for (float collumn = 0; collumn < length; collumn = collumn + increment) {
            drawSquareYZ(line, collumn, increment);
            drawSquareYZ(line, collumn, increment, length);
        }
    }
}

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
    } else {
        cout << "Parâmetros incorretos";
    }

    return 1;
}
