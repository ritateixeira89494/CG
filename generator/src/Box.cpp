#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Box.h"

using namespace std;

ofstream box3d;
ofstream plane3d;

float zero = 0.0f;

//Draw square in ZX Axis, with y = width of box.
void drawSquareUp(float xOr, float yOr, float side, float height, int pB) {
    if (pB == 0) {
        plane3d << "(" << xOr + side << "," << height << "," << yOr << ");";
        plane3d << "(" << xOr << "," << height << "," << yOr << ");";
        plane3d << "(" << xOr << "," << height << "," << yOr + side << ")\n";

        plane3d << "(" << xOr + side << "," << height << "," << yOr + side << ");";
        plane3d << "(" << xOr + side << "," << height << "," << yOr << ");";
        plane3d << "(" << xOr << "," << height << "," << yOr + side << ")\n";
    } else {
        box3d << "(" << xOr + side << "," << height << "," << yOr << ");";
        box3d << "(" << xOr << "," << height << "," << yOr << ");";
        box3d << "(" << xOr << "," << height << "," << yOr + side << ")\n";

        box3d << "(" << xOr + side << "," << height << "," << yOr + side << ");";
        box3d << "(" << xOr + side << "," << height << "," << yOr << ");";
        box3d << "(" << xOr << "," << height << "," << yOr + side << ")\n";
    }
}

//Draw square in ZX Axis, with y = 0.
void drawSquareDown(float xOr, float yOr, float side, int pB) {
    if (pB == 0) {
        plane3d << "(" << xOr << "," << zero << "," << yOr + side << ");";
        plane3d << "(" << xOr << "," << zero << "," << yOr << ");";
        plane3d << "(" << xOr + side << "," << zero << "," << yOr << ")\n";

        plane3d << "(" << xOr << "," << zero << "," << yOr + side << ");";
        plane3d << "(" << xOr + side << "," << zero << "," << yOr << ");";
        plane3d << "(" << xOr + side << "," << zero << "," << yOr + side << ")\n";
    } else {
        box3d << "(" << xOr << "," << zero << "," << yOr + side << ");";
        box3d << "(" << xOr << "," << zero << "," << yOr << ");";
        box3d << "(" << xOr + side << "," << zero << "," << yOr << ")\n";

        box3d << "(" << xOr << "," << zero << "," << yOr + side << ");";
        box3d << "(" << xOr + side << "," << zero << "," << yOr << ");";
        box3d << "(" << xOr + side << "," << zero << "," << yOr + side << ")\n";

    }
}

//Draw square in XY Axis, with z = 0.
void drawSquareXY(float xOr, float yOr, float side) {
    box3d << "(" << xOr << "," << yOr << "," << zero << ");";
    box3d << "(" << xOr << "," << yOr + side << "," << zero << ");";
    box3d << "(" << xOr + side << "," << yOr << "," << zero << ")\n";


    box3d << "(" << xOr << "," << yOr + side << "," << zero << ");";
    box3d << "(" << xOr + side << "," << yOr + side << "," << zero << ");";
    box3d << "(" << xOr + side << "," << yOr << "," << zero << ")\n";
}

//Draw square in XY Axis, with z = 0.
void drawSquareXY(float xOr, float yOr, float side, float z) {
        //
    box3d << "(" << xOr << "," << yOr << "," << z << ");";
    box3d << "(" << xOr + side << "," << yOr << "," << z << ");";
    box3d << "(" << xOr << "," << yOr + side << "," << z << ")\n";


    box3d << "(" << xOr << "," << yOr + side << "," << z << ");";
    box3d << "(" << xOr + side << "," << yOr << "," << z << ");";
    box3d << "(" << xOr + side << "," << yOr + side << "," << z << ")\n";
}

//Draw square in YZ Axis, with x = 0.
void drawSquareYZ(float yOr, float zOr, float side) {
        //
    box3d << "(" << zero << "," << yOr + side << "," << zOr << ");";
    box3d << "(" << zero << "," << yOr << "," << zOr << ");";
    box3d << "(" << zero << "," << yOr << "," << zOr + side << ")\n";


    box3d << "(" << zero << "," << yOr << "," << zOr + side << ");";
    box3d << "(" << zero << "," << yOr + side << "," << zOr + side << ");";
    box3d << "(" << zero << "," << yOr + side << "," << zOr << ")\n";
}

//Draw square in YZ Axis, with x = length of square.
void drawSquareYZ(float yOr, float zOr, float side, float x) {
        //
    box3d << "(" << x << "," << yOr << "," << zOr << ");";
    box3d << "(" << x << "," << yOr << "," << zOr + side << ");";
    box3d << "(" << x << "," << yOr << "," << zOr << ")\n";


    box3d << "(" << x << "," << yOr << "," << zOr + side << ");";
    box3d << "(" << x << "," << yOr + side << "," << zOr << ");";
    box3d << "(" << x << "," << yOr + side << "," << zOr + side << ")\n";

}


// Desenha um plano a partir dos pontos individuais. 
// De cada ponto, sabe-se o lado de cada quadrado, logo � f�cil desenhar o resto do quadrado.
void drawPlane(float length, float divisions, string name) {
    plane3d.open(name);

    float increment = length / divisions;
    //Draw base and top
    for (float line = 0; line < length; line = line + increment) {
        for (float collumn = 0; collumn < length; collumn = collumn + increment) {
            drawSquareUp(line, collumn, increment, length, 0);
            //	drawSquareDown(line, collumn, increment, 0);
        }
    }
    plane3d.close();
}


void drawBox(float length, float divisions, string nameOfFile) {
    box3d.open(nameOfFile);

    float increment = length / divisions;
	for (float divisionX = 0, line = 0, column = 0; divisionX < divisions; line = line + increment, divisionX++) {
		for (float divisionY = 0, column = 0; divisionY < divisions; column = column + increment, divisionY++) {
            drawSquareUp(line, column, increment, length, 1); //1 -> Box, 0-> Plane
            drawSquareDown(line, column, increment, 1); //1 -> Box, 0-> Plane
            drawSquareXY(line, column, increment);
            drawSquareXY(line, column, increment, length);
            drawSquareYZ(line, column, increment);
            drawSquareYZ(line, column, increment, length);
        }
    }
    //drawPlane(length, divisions);
    //drawPlaneXY(length, divisions);
    //drawPlaneYZ(length, divisions);

}