#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
#include <tuple>

#include "primitives/Piramide.h"
#include "utils/utils.h"

using namespace std;

/*!
    Here we describe the points that are compose the base of the pyramid. 
    We use polar coordinates, and write to the file that is open in piramide3d.
*/
void
drawBasePyramid(float radius, int height, int slices, int stacks, ofstream *file, ofstream *norm_file, ofstream &text) {
    float currentRadius;
    float zero = 0.0f;
    float alfa = 2 * M_PI / slices;
    float proxRadius = alfa;
    float y = 0;


    for (currentRadius = 0; currentRadius < 2 * M_PI; currentRadius += alfa, proxRadius += alfa) {
        //Draw triangle in base
        // Vertices
        auto p1 = make_tuple(0.0f, y, 0.0f);
        auto p2 = make_tuple(radius * cos(currentRadius), y, radius * sin(currentRadius));
        auto p3 = make_tuple(radius * cos(proxRadius), y, radius * sin(proxRadius));

        // Normals
        auto normal = make_tuple(0, -1, 0);

        // Textures
        auto t1 = make_tuple(0, 0);
        auto t2 = make_tuple(0, 1);
        auto t3 = make_tuple(1, 1);

        // Vertices
        write_triangle(p1, p2, p3, file);

        // Normals
        write_triangle(normal, normal, normal, norm_file);
        // TODO: Base is removed

        // Textures
        write_text_triangule(t1, t2, t3, text);
    }

}

void drawPyramid(float radius, float height, int slices, float stacks, string nameFile) {
    ofstream file;
    file.open(nameFile);

    string normalPath = replace_extension(nameFile, "normal");
    ofstream normalFile;
    normalFile.open(normalPath);

    // Texture file
    ofstream text_file;
    text_file.open(nameFile.substr(0, nameFile.length() - 3) + ".text");

    drawBasePyramid(radius, height, slices, stacks, &file, &normalFile, text_file);

    float currentHeight = 0;
    float h = height / stacks;

    float currentRadius = 0;
    float zero = 0.0f;
    float alfa = (2.f * (float) M_PI) / ((float) slices);
    float proxRadius = alfa;

    float incX_bitmap = 1.0f / ((float) slices);
    float incY_bitmap = 1.0f / ((float) stacks);


    float thisRadius;
    float nextRadius;

    tuple<float, float, float> normal;
    tuple<float, float, float> next_normal;

    float current_x_bitmap = 0;
    float current_y_bitmap = 0;
    int vertex = 0;
    for (currentRadius = 0, current_y_bitmap = 0;
         currentRadius < 2 * M_PI; currentRadius += alfa, proxRadius += alfa, current_x_bitmap += incX_bitmap) {
        for (currentHeight = 0, current_y_bitmap = 0;
             currentHeight < height; currentHeight += h, current_y_bitmap += incY_bitmap) {

            thisRadius = ((height - currentHeight) * radius) / height;
            nextRadius = ((height - currentHeight - h) * radius) / height;
            if (nextRadius < 0) nextRadius = 0;

            // Vertices
            auto p1 = make_tuple(thisRadius * cos(proxRadius), currentHeight, thisRadius * sin(proxRadius));
            auto p2 = make_tuple(thisRadius * cos(currentRadius), currentHeight, thisRadius * sin(currentRadius));
            auto p3 = make_tuple(nextRadius * cos(proxRadius), currentHeight + h, nextRadius * sin(proxRadius));

            auto p4 = make_tuple(nextRadius * cos(currentRadius), currentHeight + h, nextRadius * sin(currentRadius));
            auto p5 = make_tuple(nextRadius * cos(proxRadius), currentHeight + h, nextRadius * sin(proxRadius));
            auto p6 = make_tuple(thisRadius * cos(currentRadius), currentHeight, thisRadius * sin(currentRadius));


            // Normals
            if (currentHeight == 0) {
                auto vector = make_tuple(-get<0>(p1), height, -get<2>(p1));
                auto tangent_p1 = normalize(cross(p1, make_tuple(0, 1, 0)));
                auto tangent_p2 = normalize(cross(p2, make_tuple(0, 1, 0)));

                normal = normalize(cross(vector, tangent_p2));
                next_normal = normalize(cross(vector, tangent_p1));
            }

            auto normal_p1 = next_normal;
            auto normal_p2 = normal;
            auto normal_p3 = next_normal;

            auto normal_p4 = normal;
            auto normal_p5 = next_normal;
            auto normal_p6 = normal;

            // Texture coordinates
            auto t1 = make_tuple(current_x_bitmap + incX_bitmap, current_y_bitmap);
            auto t2 = make_tuple(current_x_bitmap, current_y_bitmap);
            auto t3 = make_tuple(current_x_bitmap + incX_bitmap, current_y_bitmap + incY_bitmap);

            auto t4 = make_tuple(current_x_bitmap, current_y_bitmap + incY_bitmap);
            auto t5 = make_tuple(current_x_bitmap + incX_bitmap, current_y_bitmap + incY_bitmap);
            auto t6 = make_tuple(current_x_bitmap, current_y_bitmap);

            // Vertices
            write_triangle(p1, p2, p3, &file);
            write_triangle(p4, p5, p6, &file);

            // Normals
            write_triangle(normal_p1, normal_p2, normal_p3, &normalFile);
            write_triangle(normal_p4, normal_p5, normal_p6, &normalFile);

            // Textures
            write_text_triangule(t1, t2, t3, text_file);
            write_text_triangule(t4, t5, t6, text_file);
        }
    }

    file.close();
    normalFile.close();
    text_file.close();
}
