#include <string>
#include <fstream>
#include <cmath>

#include "primitives/Piramide.h"
#include "utils/utils.h"

using namespace std;

/*!
    Here we describe the points that are compose the base of the pyramid. 
    We use polar coordinates, and write to the file that is open in piramide3d.
*/
void drawBasePyramid(float radius, int height, int slices, int stacks, ofstream *file, ofstream &text) {
    float currentRadius;
    float zero = 0.0f;
    float alfa = 2 * M_PI / slices;
    float proxRadius = alfa;
    float y = 0;


    for (currentRadius = 0; currentRadius < 2 * M_PI; currentRadius += alfa, proxRadius += alfa) {
        //Draw triangle in base
        auto p1 = make_tuple(0.0f, y, 0.0f);
        auto p2 = make_tuple(radius * cos(currentRadius), y, radius * sin(currentRadius));
        auto p3 = make_tuple(radius * cos(proxRadius), y, radius * sin(proxRadius));

        auto t1 = make_tuple(0, 0);
        auto t2 = make_tuple(0, 1);
        auto t3 = make_tuple(1, 1);

        write_triangle(p1, p2, p3, file);

        write_text_triangule(t1, t2, t3, text);
    }

}

void drawPyramid(float radius, float height, int slices, float stacks, string nameFile) {

    ofstream file;
    file.open(nameFile);

    // Texture file
    ofstream text_file;
    text_file.open(nameFile.substr(0, nameFile.length() - 3) + ".text");


    drawBasePyramid(radius, height, slices, stacks, &file, text_file);

    float currentHeight = 0;
    float h = height / stacks;

    float currentRadius = 0;
    float zero = 0.0f;
    float alfa = (2 * M_PI) / slices;
    float proxRadius = alfa;

    float incX_bitmap = 1.0f / ((float) slices);
    float incY_bitmap = 1.0f / ((float) stacks);


    float thisRadius;
    float nextRadius;

    float current_x_bitmap = 0;
    float current_y_bitmap = 0;
    int vertex = 0;
    for (currentRadius = 0, current_x_bitmap = 0;
         currentRadius < 2 * M_PI; currentRadius += alfa, proxRadius += alfa, current_x_bitmap += incX_bitmap) {
        for (currentHeight = 0, current_y_bitmap = 0;
             currentHeight < height; currentHeight += h, current_y_bitmap += incY_bitmap) {

            thisRadius = ((height - currentHeight) * radius) / height;
            nextRadius = ((height - currentHeight - h) * radius) / height;
            if (nextRadius < 0) nextRadius = 0;

            auto p1 = make_tuple(thisRadius * cos(proxRadius), currentHeight, thisRadius * sin(proxRadius));
            auto p2 = make_tuple(thisRadius * cos(currentRadius), currentHeight, thisRadius * sin(currentRadius));
            auto p3 = make_tuple(nextRadius * cos(proxRadius), currentHeight + h, nextRadius * sin(proxRadius));

            auto p4 = make_tuple(nextRadius * cos(currentRadius), currentHeight + h, nextRadius * sin(currentRadius));
            auto p5 = make_tuple(nextRadius * cos(proxRadius), currentHeight + h, nextRadius * sin(proxRadius));
            auto p6 = make_tuple(thisRadius * cos(currentRadius), currentHeight, thisRadius * sin(currentRadius));

            // Texture coordenates
            auto t1 = make_tuple(current_x_bitmap + incX_bitmap, current_y_bitmap);
            auto t2 = make_tuple(current_x_bitmap, current_y_bitmap);
            auto t3 = make_tuple(current_x_bitmap + incX_bitmap, current_y_bitmap + incY_bitmap);

            auto t4 = make_tuple(current_x_bitmap, current_y_bitmap + incY_bitmap);
            auto t5 = make_tuple(current_x_bitmap + incX_bitmap, current_y_bitmap + incY_bitmap);
            auto t6 = make_tuple(current_x_bitmap, current_y_bitmap);

            // Generating the triangles
            write_triangle(p1, p2, p3, &file);
            write_triangle(p4, p5, p6, &file);

            // Generating the texture coordenates
            write_text_triangule(t1, t2, t3, text_file);
            write_text_triangule(t4, t5, t6, text_file);
        }
    }

    file.close();
}
