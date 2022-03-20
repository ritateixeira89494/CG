#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

#include "Box.h"
#include "Plane.h"
#include "utils.h"

using namespace std;

/*!
  In the following functions we draw each face of the box. 
  We choose this method because it's easier to debug and to analyse strange behaviours. 
  In each function we write to the file, that is open in plane3d or box3d, depending on what function was called.

    The xOr (original x), yOr or zOr describe where the square should start, the blue point in the first figure of the report.
    
  In this function we draw a square in XY Axis, with z = 0.
*/
void drawSquareXY(float xOr, float yOr, float edge, ofstream *file) {
    auto p1 = make_tuple(xOr, yOr, 0.0f);
    auto p2 = make_tuple(xOr, yOr + edge, 0.0f);
    auto p3 = make_tuple(xOr + edge, yOr, 0.0f);

    auto p4 = make_tuple(xOr, yOr + edge, 0.0f);
    auto p5 = make_tuple(xOr + edge, yOr + edge, 0.0f);
    auto p6 = make_tuple(xOr + edge, yOr, 0.0f);

    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);
}

/*!
  Draw square in XY Axis, with z != 0.
*/
void drawSquareXY(float xOr, float yOr, float edge, float z, ofstream *file) {
    auto p1 = make_tuple(xOr, yOr, z);
    auto p2 = make_tuple(xOr + edge, yOr + edge, z);
    auto p3 = make_tuple(xOr, yOr + edge, z);

    auto p4 = make_tuple(xOr, yOr, z);
    auto p5 = make_tuple(xOr + edge, yOr, z);
    auto p6 = make_tuple(xOr + edge, yOr + edge, z);

    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);
}

/*!
    Draw square in YZ Axis, with x = 0.
*/
void drawSquareYZ(float yOr, float zOr, float edge, ofstream *file) {
    auto p1 = make_tuple(0.0f, yOr + edge, zOr);
    auto p2 = make_tuple(0.0f, yOr, zOr);
    auto p3 = make_tuple(0.0f, yOr, zOr + edge);

    auto p4 = make_tuple(0.0f, yOr + edge, zOr + edge);
    auto p5 = make_tuple(0.0f, yOr + edge, zOr);
    auto p6 = make_tuple(0.0f, yOr, zOr + edge);

    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);
}

/*!
    Draw square in YZ Axis, with x = length of square.
*/
void drawSquareYZ(float yOr, float zOr, float edge, float x, ofstream *file) {
    auto p1 = make_tuple(x, yOr + edge, zOr);
    auto p2 = make_tuple(x, yOr, zOr + edge);
    auto p3 = make_tuple(x, yOr, zOr);

    auto p4 = make_tuple(x, yOr, zOr + edge);
    auto p5 = make_tuple(x, yOr + edge, zOr);
    auto p6 = make_tuple(x, yOr + edge, zOr + edge);

    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);
}

void drawBox(float length, float divisions, string nameOfFile) {
    ofstream file;
    file.open(nameOfFile);

    float increment = length / divisions;
	for (float divisionX = 0, line = 0, column = 0; divisionX < divisions; line = line + increment, divisionX++) {
		for (float divisionY = 0, column = 0; divisionY < divisions; column = column + increment, divisionY++) {
            drawSquareUp(line, column, increment, length, &file); //1 -> Box, 0-> Plane
            drawSquareDown(line, column, increment, &file); //1 -> Box, 0-> Plane
            drawSquareXY(line, column, increment, &file);
            drawSquareXY(line, column, increment, length, &file);
            drawSquareYZ(line, column, increment, &file);
            drawSquareYZ(line, column, increment, length, &file);
        }
    }
}
