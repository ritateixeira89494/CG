#include <iostream>
#include <string>
#include <fstream>
#include <GL/glut.h>


#include <stdio.h>
#include <math.h>


using namespace std;

ofstream piramide3d;


void drawBasePyramid(float radius, int height, int slices, int stacks) {
    float currentRadius;
    float zero = 0.0f;
    float alfa = 2 * M_PI / slices;
    float proxRadius = alfa;
    float y = 0;


    for (currentRadius = 0; currentRadius < 2 * M_PI; currentRadius += alfa, proxRadius += alfa) {
        // X axis in red
        //Draw triangle in base
        piramide3d << "(" << zero << "," << y << "," << zero << ");";
        piramide3d << "(" << radius * cos(currentRadius) << "," << y << "," << radius * sin(currentRadius) << ");";
        piramide3d << "(" << radius * cos(proxRadius) << "," << y << "," << radius * sin(proxRadius) << ")\n";


    }

}

void drawPyramid(float radius, float height, int slices, float stacks, string nameFile) {

    piramide3d.open(nameFile);
    //piramide3d << "piramide.3d\n";

    drawBasePyramid(radius, height, slices, stacks);

    float currentHeight = 0;
    float h = height / stacks;

    float currentRadius = 0;
    float zero = 0.0f;
    float alfa = (2 * M_PI) / slices;
    float proxRadius = alfa;
    //printf("Altura incrementa: %f", h);

    float thisRadio;
    float nextRadio;

    for (currentRadius = 0; currentRadius < 2 * M_PI; currentRadius += alfa, proxRadius += alfa) {
        for (currentHeight = 0; currentHeight < height; currentHeight += h) {

            thisRadio = ((height - currentHeight) * radius) / height;
            nextRadio = ((height - currentHeight - h) * radius) / height;
            if (nextRadio < 0) nextRadio = 0;
            piramide3d << "(" << thisRadio * cos(proxRadius) << "," << currentHeight << ","
                       << thisRadio * sin(proxRadius) << ");";
            piramide3d << "(" << thisRadio * cos(currentRadius) << "," << currentHeight << ","
                       << thisRadio * sin(currentRadius) << ");";
            piramide3d << "(" << nextRadio * cos(proxRadius) << "," << currentHeight + h << ","
                       << nextRadio * sin(proxRadius) << ")\n";


            piramide3d << "(" << nextRadio * cos(currentRadius) << "," << currentHeight + h << ","
                       << nextRadio * sin(currentRadius) << ");";
            piramide3d << "(" << nextRadio * cos(proxRadius) << "," << currentHeight + h << ","
                       << nextRadio * sin(proxRadius) << ");";
            piramide3d << "(" << thisRadio * cos(currentRadius) << "," << currentHeight << ","
                       << thisRadio * sin(currentRadius) << ")\n";

        }

    }

    piramide3d.close();
}
