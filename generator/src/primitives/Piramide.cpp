#include <string>
#include <fstream>
#include <cmath>
#include <tuple>

#include "primitives/Piramide.h"
#include "utils/utils.h"

using namespace std;

/*!
    Here we describe the points that are compose the base of the pyramid. 
    We use polar coordinates, and write to the file that is open in piramide3d.
*/
void drawBasePyramid(float radius, int height, int slices, int stacks, ofstream *file, ofstream *norm_file) {
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
        
        auto normal = make_tuple(0,-1,0);

        write_triangle(p1, p2, p3, file);
        write_triangle(normal,normal,normal, norm_file);
    }

}

void drawPyramid(float radius, float height, int slices, float stacks, string nameFile) {

    ofstream file;
    file.open(nameFile);

    string normalPath = replace_extension(nameFile, "normal");
    ofstream normalFile;
    normalFile.open(normalPath);

    drawBasePyramid(radius, height, slices, stacks, &file, &normalFile);

    float currentHeight = 0;
    float h = height / stacks;

    float currentRadius = 0;
    float zero = 0.0f;
    float alfa = (2 * M_PI) / slices;
    float proxRadius = alfa;

    float thisRadius;
    float nextRadius;

    tuple<float,float,float> normal;
    tuple<float,float,float> next_normal;

    for (currentRadius = 0; currentRadius < 2 * M_PI; currentRadius += alfa, proxRadius += alfa) {
        for (currentHeight = 0; currentHeight < height; currentHeight += h) {

            thisRadius = ((height - currentHeight) * radius) / height;
            nextRadius = ((height - currentHeight - h) * radius) / height;
            if (nextRadius < 0) nextRadius = 0;

            auto p1 = make_tuple(thisRadius * cos(proxRadius), currentHeight, thisRadius * sin(proxRadius));
            auto p2 = make_tuple(thisRadius * cos(currentRadius), currentHeight, thisRadius * sin(currentRadius));
            auto p3 = make_tuple(nextRadius * cos(proxRadius), currentHeight + h, nextRadius * sin(proxRadius));

            auto p4 = make_tuple(nextRadius * cos(currentRadius), currentHeight + h, nextRadius * sin(currentRadius));
            auto p5 = make_tuple(nextRadius * cos(proxRadius), currentHeight + h, nextRadius * sin(proxRadius));
            auto p6 = make_tuple(thisRadius * cos(currentRadius), currentHeight, thisRadius * sin(currentRadius));

            write_triangle(p1, p2, p3, &file);
            write_triangle(p4, p5, p6, &file);

            if (currentHeight == 0) {
                auto vector = make_tuple(-get<0>(p1),height,-get<2>(p1));
                auto tangent_p1 = normalize( cross(p1,make_tuple(0,1,0)) );
                auto tangent_p2 = normalize( cross(p2,make_tuple(0,1,0)) );

                normal      = normalize( cross(vector,tangent_p2) );
                next_normal = normalize( cross(vector,tangent_p1) );
            }

            auto normal_p1 = next_normal;
            auto normal_p2 = normal;
            auto normal_p3 = next_normal;

            auto normal_p4 = normal;
            auto normal_p5 = next_normal;
            auto normal_p6 = normal;

            write_triangle(normal_p1, normal_p2, normal_p3, &normalFile);
            write_triangle(normal_p4, normal_p5, normal_p6, &normalFile);
        }
    }

    file.close();
}
