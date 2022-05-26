#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>

#include "primitives/Box.h"
#include "primitives/Plane.h"
#include "utils/utils.h"

using namespace std;

/*!
  In the following functions we draw each face of the box. 
  We choose this method because it's easier to debug and to analyse strange behaviours. 
  In each function we write to the file, that is open in plane3d or box3d, depending on what function was called.

    The xOr (original x), yOr or zOr describe where the square should start, the blue point in the first figure of the report.
    
  In this function we draw a square in XY Axis, with z = 0.
*/
void drawSquareXY(float xOr, float yOr, float edge, ofstream *vertexFile, ofstream *normalFile, float origin) {
    auto p1 = make_tuple(xOr, yOr, -origin);
    auto p2 = make_tuple(xOr, yOr + edge, -origin);
    auto p3 = make_tuple(xOr + edge, yOr, -origin);

    auto p4 = make_tuple(xOr, yOr + edge, -origin);
    auto p5 = make_tuple(xOr + edge, yOr + edge, -origin);
    auto p6 = make_tuple(xOr + edge, yOr, -origin);

    auto p7 = make_tuple(xOr, yOr, origin);
    auto p9 = make_tuple(xOr + edge, yOr + edge, origin);
    auto p8 = make_tuple(xOr, yOr + edge, origin);

    auto p10 = make_tuple(xOr, yOr, origin);
    auto p11 = make_tuple(xOr + edge, yOr, origin);
    auto p12 = make_tuple(xOr + edge, yOr + edge, origin);

    write_triangle(p1, p2, p3, vertexFile);
    write_triangle(p4, p5, p6, vertexFile);
    write_triangle(p8, p7, p9, vertexFile);
    write_triangle(p10, p11, p12, vertexFile);

    // Normals
    auto normal_pos = make_tuple(0,0,-1); 
    auto normal_neg = make_tuple(0,0,1);
    write_triangle(normal_pos, normal_pos, normal_pos, normalFile);
    write_triangle(normal_pos, normal_pos, normal_pos, normalFile);
    write_triangle(normal_neg, normal_neg, normal_neg, normalFile);
    write_triangle(normal_neg, normal_neg, normal_neg, normalFile);
}


/*!
    Draw square in YZ Axis, with x = 0.
*/
void drawSquareYZ(float yOr, float zOr, float edge, ofstream *vertexFile, ofstream *normalFile, float origin) {
    auto p1 = make_tuple(-origin, yOr + edge, zOr);
    auto p2 = make_tuple(-origin, yOr, zOr);
    auto p3 = make_tuple(-origin, yOr, zOr + edge);

    auto p4 = make_tuple(-origin, yOr + edge, zOr + edge);
    auto p5 = make_tuple(-origin, yOr + edge, zOr);
    auto p6 = make_tuple(-origin, yOr, zOr + edge);

    auto p7 = make_tuple(origin, yOr + edge, zOr);
    auto p8 = make_tuple(origin, yOr, zOr + edge);
    auto p9 = make_tuple(origin, yOr, zOr);

    auto p10 = make_tuple(origin, yOr, zOr + edge);
    auto p11 = make_tuple(origin, yOr + edge, zOr);
    auto p12 = make_tuple(origin, yOr + edge, zOr + edge);

    // Vertices
    write_triangle(p1, p2, p3, vertexFile);
    write_triangle(p4, p5, p6, vertexFile);
    write_triangle(p7, p8, p9, vertexFile);
    write_triangle(p10, p11, p12, vertexFile);
    
    // Normals
    auto normal_pos = make_tuple(-1,0,0); 
    auto normal_neg = make_tuple(1,0,0);
    write_triangle(normal_pos, normal_pos, normal_pos, normalFile);
    write_triangle(normal_pos, normal_pos, normal_pos, normalFile);
    write_triangle(normal_neg, normal_neg, normal_neg, normalFile);
    write_triangle(normal_neg, normal_neg, normal_neg, normalFile);
}

void drawBox(float length, float divisions, string nameOfFile) {
    ofstream vertexFile;
    vertexFile.open(nameOfFile);

    string normalpath = replace_extension(nameOfFile, "normal");
    ofstream normalFile;
    normalFile.open(normalpath);

    float increment = length / divisions;
    for (float divisionX = 0, line = -length / 2, column = -length / 2;
         divisionX < divisions; line = line + increment, divisionX++) {
        for (float divisionY = 0, column = -length / 2;
             divisionY < divisions; column = column + increment, divisionY++) {
            drawSquareUp(line, column, increment, length / 2, &vertexFile, &normalFile); //1 -> Box, 0-> Plane
            drawSquareDown(line, column, increment, &vertexFile, &normalFile, length / 2); //1 -> Box, 0-> Plane
            drawSquareXY(line, column, increment, &vertexFile, &normalFile, length / 2);
            drawSquareYZ(line, column, increment, &vertexFile, &normalFile, length / 2);
        }
    }

    vertexFile.close();
    normalFile.close();
}
