#include <tuple>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "primitives/Sphere.h"
#include "utils/utils.h"

using namespace std;

//Draw square in ZX Axis, with y = higth of box.
void drawSquareUpT(float xOr, float yOr, float edge, float height, ofstream *file) {
    auto p1 = make_tuple(xOr + edge, height, yOr);
    auto p2 = make_tuple(xOr, height, yOr);
    auto p3 = make_tuple(xOr, height, yOr + edge);

    auto p4 = make_tuple(xOr + edge, height, yOr + edge);
    auto p5 = make_tuple(xOr + edge, height, yOr);
    auto p6 = make_tuple(xOr, height, yOr + edge);

    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);
}

/*!
    In this function we describe the points of the parallelograms.
    We need the alfas and betas of the four points, but the radius is the same because it is a sphere. 
    Also, we start by calculating each point, and then we write them to files.
*/
void
drawFaceSphere(float currentalfa, float proxAlfa, float currentBeta, float proxBeta, float radius, ofstream *file,
               float current_y_bitmap, float increment_Y_bitmap, float current_x_bitmap, float increment_X_bitmap,
               ofstream *norm_file, ofstream &text) {
    // Point 1
    float x1 = radius * cos(currentBeta) * sin(currentalfa);
    float y1 = radius * sin(currentBeta);
    float z1 = radius * cos(currentBeta) * cos(currentalfa);

    // Point 2
    float x2 = radius * cos(currentBeta) * sin(proxAlfa);
    float y2 = radius * sin(currentBeta);
    float z2 = radius * cos(currentBeta) * cos(proxAlfa);

    // Point 3
    float x3 = radius * cos(proxBeta) * sin(currentalfa);
    float y3 = radius * sin(proxBeta);
    float z3 = radius * cos(proxBeta) * cos(currentalfa);

    // Point 4
    float x4 = radius * cos(proxBeta) * sin(proxAlfa);
    float y4 = radius * sin(proxBeta);
    float z4 = radius * cos(proxBeta) * cos(proxAlfa);

    // Texture stuff
    float x1t = current_x_bitmap;
    float y1t = current_y_bitmap;

    float x2t = current_x_bitmap + increment_X_bitmap;
    float y2t = current_y_bitmap;

    float x3t = current_x_bitmap;
    float y3t = current_y_bitmap + increment_Y_bitmap;

    float x4t = current_x_bitmap + increment_X_bitmap;
    float y4t = current_y_bitmap + increment_Y_bitmap;


    // Texture points
    tuple<float, float> t1;
    tuple<float, float> t2;
    tuple<float, float> t3;
    tuple<float, float> t4;
    tuple<float, float> t5;
    tuple<float, float> t6;


    ////

    tuple<float, float, float> p1;
    tuple<float, float, float> p2;
    tuple<float, float, float> p3;
    tuple<float, float, float> p4;
    tuple<float, float, float> p5;
    tuple<float, float, float> p6;

    if (currentBeta > 0 || proxBeta > 0) {
        p1 = make_tuple(x3, y3, z3);
        p2 = make_tuple(x1, y1, z1);
        p3 = make_tuple(x2, y2, z2);

        p4 = make_tuple(x4, y4, z4);
        p5 = make_tuple(x3, y3, z3);
        p6 = make_tuple(x2, y2, z2);

        // Texture
        t1 = make_tuple(x3t, y3t);
        t2 = make_tuple(x1t, y1t);
        t3 = make_tuple(x2t, y2t);

        t4 = make_tuple(x4t, y4t);
        t5 = make_tuple(x3t, y3t);
        t6 = make_tuple(x2t, y2t);
    } else {
        p1 = make_tuple(x3, y3, z3);
        p2 = make_tuple(x2, y2, z2);
        p3 = make_tuple(x1, y1, z1);

        p4 = make_tuple(x4, y4, z4);
        p5 = make_tuple(x2, y2, z2);
        p6 = make_tuple(x3, y3, z3);

        // Texture
        t1 = make_tuple(x3t, y3t);
        t2 = make_tuple(x2t, y2t);
        t3 = make_tuple(x1t, y1t);

        t4 = make_tuple(x4t, y4t);
        t5 = make_tuple(x2t, y2t);
        t6 = make_tuple(x3t, y3t);
    }

    // Vertices
    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);

    // Normals
    tuple<float, float, float> p1_norm = normalize(make_tuple(get<0>(p1), get<1>(p1), get<2>(p1)));
    tuple<float, float, float> p2_norm = normalize(make_tuple(get<0>(p2), get<1>(p2), get<2>(p2)));
    tuple<float, float, float> p3_norm = normalize(make_tuple(get<0>(p3), get<1>(p3), get<2>(p3)));
    tuple<float, float, float> p4_norm = normalize(make_tuple(get<0>(p4), get<1>(p4), get<2>(p4)));
    tuple<float, float, float> p5_norm = normalize(make_tuple(get<0>(p5), get<1>(p5), get<2>(p5)));
    tuple<float, float, float> p6_norm = normalize(make_tuple(get<0>(p6), get<1>(p6), get<2>(p6)));

    write_triangle(p1_norm, p2_norm, p3_norm, norm_file);
    write_triangle(p4_norm, p5_norm, p6_norm, norm_file);

    // Textures
    write_text_triangule(t1, t2, t3, text);
    write_text_triangule(t4, t5, t6, text);

}

/*!
    In this function we describe all points, in both alfa and beta coordinates.
	Also, we divide each level of the sphere in parallelograms.
*/
void drawTopSphere(int radius, int slices, int stacks, ofstream *file, ofstream *norm_file, ofstream &text) {
    //Alfa = xOz plano
    float incrementAlfa = 2.f * M_PI / slices;
    float currentalfa;
    float zero = 0.0f;
    float proxAlfa;

    //Beta = Mexer no y
    float incrementBeta = M_PI / (2 * stacks);
    float currentBeta;
    float proxBeta;

    // Bitmap part
    float increment_X_bitmap = 1.0f / ((float) stacks);
    float increment_Y_bitmap = 1.0f / ((float) slices);
    // O x avança por faixas verticais
    float current_x_bitmap = 0;
    // Mas o y avança em paralelo, de 0.5 para cima e baixo ao mesmo tempo, porque desenhamos as duas faces da esfera assim.
    float current_y_bitmap = 0;

    for (currentBeta = 0, proxBeta = incrementBeta;
         currentBeta < (M_PI / 2); currentBeta += incrementBeta, proxBeta += incrementBeta) {
        for (currentalfa = 0, proxAlfa = incrementAlfa;
             currentalfa < 2 * M_PI; currentalfa += incrementAlfa, proxAlfa += incrementAlfa) {
            drawFaceSphere(currentalfa, proxAlfa, currentBeta, proxBeta, radius, file, current_y_bitmap,
                           increment_Y_bitmap, current_x_bitmap, increment_X_bitmap, norm_file, text);
            drawFaceSphere(currentalfa, proxAlfa, -currentBeta, -proxBeta, radius, file, -current_y_bitmap,
                           -increment_Y_bitmap, current_x_bitmap, increment_X_bitmap, norm_file, text);
        }
    }
}

/*!
    In this function we open and close the necessary file, and call the function that describes the sphere.
*/
void drawSphere(int radius, int slices, int stacks, string filename) {
    // Vertices file
    ofstream file;
    file.open(filename);

    // Normal file
    string normalPath = replace_extension(filename, "normal");
    ofstream normalFile;
    normalFile.open(normalPath);

    // Texture file
    ofstream text_file;
    text_file.open(filename.substr(0, filename.length() - 3) + ".text");

    drawTopSphere(radius, slices, stacks / 2, &file, &normalFile, text_file);

    file.close();
    normalFile.close();
    text_file.close();
}


