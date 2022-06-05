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
void drawSquareXY(float xOr, float yOr, float edge, ofstream *vertexFile, ofstream *normalFile, float origin,
                  ofstream &text_file) {
    // Usefull points
    auto p1 = make_tuple(xOr, yOr, -origin); // (0, 0)
    auto p2 = make_tuple(xOr, yOr + edge, -origin); // (0, 1)
    auto p3 = make_tuple(xOr + edge, yOr, -origin); // (1, 0)

    auto p4 = make_tuple(xOr, yOr + edge, -origin); // (0, 1)
    auto p5 = make_tuple(xOr + edge, yOr + edge, -origin); // (1, 1)
    auto p6 = make_tuple(xOr + edge, yOr, -origin); // (1, 0)

    auto p7 = make_tuple(xOr, yOr, origin); // (0, 0)
    auto p9 = make_tuple(xOr + edge, yOr + edge, origin); // (1, 1)
    auto p8 = make_tuple(xOr, yOr + edge, origin); // (0, 1)

    auto p10 = make_tuple(xOr, yOr, origin); // (0, 0)
    auto p11 = make_tuple(xOr + edge, yOr, origin); // (1, 0)
    auto p12 = make_tuple(xOr + edge, yOr + edge, origin); // (1, 1)

    // Normals vectors
    auto normal_pos = make_tuple(0, 0, -1);
    auto normal_neg = make_tuple(0, 0, 1);

    // Texture coordenates
    auto t1 = make_tuple(0, 0);
    auto t2 = make_tuple(0, 1);
    auto t3 = make_tuple(1, 0);

    auto t4 = make_tuple(0, 1);
    auto t5 = make_tuple(1, 1);
    auto t6 = make_tuple(1, 0);

    auto t7 = make_tuple(0, 0);
    auto t8 = make_tuple(1, 1);
    auto t9 = make_tuple(0, 1);

    auto t10 = make_tuple(0, 0);
    auto t11 = make_tuple(1, 0);
    auto t12 = make_tuple(1, 1);

    // Generating the triangles
    write_triangle(p1, p2, p3, vertexFile);
    write_triangle(p4, p5, p6, vertexFile);
    write_triangle(p8, p7, p9, vertexFile);
    write_triangle(p10, p11, p12, vertexFile);

    // Normals
    write_triangle(normal_pos, normal_pos, normal_pos, normalFile);
    write_triangle(normal_pos, normal_pos, normal_pos, normalFile);
    write_triangle(normal_neg, normal_neg, normal_neg, normalFile);
    write_triangle(normal_neg, normal_neg, normal_neg, normalFile);

    // Generating the texture coordenates
    write_text_triangule(t1, t2, t3, text_file);
    write_text_triangule(t4, t5, t6, text_file);
    write_text_triangule(t7, t8, t9, text_file);
    write_text_triangule(t10, t11, t12, text_file);
}


/*!
    Draw square in YZ Axis, with x = 0.
*/
void drawSquareYZ(float yOr, float zOr, float edge, ofstream *vertexFile, ofstream *normalFile, float origin,
                  ofstream &text_file) {
    // Usefull points
    auto p1 = make_tuple(-origin, yOr + edge, zOr); // (1, 0)
    auto p2 = make_tuple(-origin, yOr, zOr); // (0, 0)
    auto p3 = make_tuple(-origin, yOr, zOr + edge); // (0, 1)

    auto p4 = make_tuple(-origin, yOr + edge, zOr + edge); // (1, 1)
    auto p5 = make_tuple(-origin, yOr + edge, zOr); // (1, 0)
    auto p6 = make_tuple(-origin, yOr, zOr + edge); // (0, 1)

    auto p7 = make_tuple(origin, yOr + edge, zOr); // (1, 0)
    auto p8 = make_tuple(origin, yOr, zOr + edge); // (0, 1)
    auto p9 = make_tuple(origin, yOr, zOr); // (0, 0)

    auto p10 = make_tuple(origin, yOr, zOr + edge); // (0, 1)
    auto p11 = make_tuple(origin, yOr + edge, zOr); // (1, 0)
    auto p12 = make_tuple(origin, yOr + edge, zOr + edge); // (1, 1)

    // Normal vectors
    auto normal_pos = make_tuple(-1, 0, 0);
    auto normal_neg = make_tuple(1, 0, 0);

    // Texture coordinates
    auto t1 = make_tuple(1, 0);
    auto t2 = make_tuple(0, 0);
    auto t3 = make_tuple(0, 1);

    auto t4 = make_tuple(1, 1);
    auto t5 = make_tuple(1, 0);
    auto t6 = make_tuple(0, 1);

    auto t7 = make_tuple(1, 0);
    auto t8 = make_tuple(0, 1);
    auto t9 = make_tuple(0, 0);

    auto t10 = make_tuple(0, 1);
    auto t11 = make_tuple(1, 0);
    auto t12 = make_tuple(1, 1);

    // Generating the triangles
    write_triangle(p1, p2, p3, vertexFile);
    write_triangle(p4, p5, p6, vertexFile);
    write_triangle(p7, p8, p9, vertexFile);
    write_triangle(p10, p11, p12, vertexFile);

    // Normals
    write_triangle(normal_pos, normal_pos, normal_pos, normalFile);
    write_triangle(normal_pos, normal_pos, normal_pos, normalFile);
    write_triangle(normal_neg, normal_neg, normal_neg, normalFile);
    write_triangle(normal_neg, normal_neg, normal_neg, normalFile);

    // Generating the texture coordenates
    write_text_triangule(t1, t2, t3, text_file);
    write_text_triangule(t4, t5, t6, text_file);
    write_text_triangule(t7, t8, t9, text_file);
    write_text_triangule(t10, t11, t12, text_file);
}

void drawBox(float length, float divisions, string nameOfFile) {
    ofstream vertexFile;
    vertexFile.open(nameOfFile);

    string normalpath = replace_extension(nameOfFile, "normal");
    ofstream normalFile;
    normalFile.open(normalpath);

    // Texture file
    ofstream texture_file;
    texture_file.open(nameOfFile.substr(0, nameOfFile.length() - 3) + ".text");

    float increment = length / divisions;
    for (float divisionX = 0, line = -length / 2, column = -length / 2;
         divisionX < divisions; line = line + increment, divisionX++) {
        for (float divisionY = 0, column = -length / 2;
             divisionY < divisions; column = column + increment, divisionY++) {
            drawSquareUp(line, column, increment, length / 2, &vertexFile, &normalFile,
                         texture_file); //1 -> Box, 0-> Plane
            drawSquareDown(line, column, increment, &vertexFile, &normalFile, length / 2,
                           texture_file); //1 -> Box, 0-> Plane
            drawSquareXY(line, column, increment, &vertexFile, &normalFile, length / 2, texture_file);
            drawSquareYZ(line, column, increment, &vertexFile, &normalFile, length / 2, texture_file);
        }
    }

    texture_file.close();

    vertexFile.close();
    normalFile.close();
}
