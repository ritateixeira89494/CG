#include <fstream>
#include <string>
#include <tuple>
#include "utils/utils.h"

using namespace std;

//Draw square in ZX Axis, with y = 0.
void drawSquareDown(float xOr, float yOr, float edge, ofstream *vertexFile, ofstream *normalFile, float origin) {
    auto p1 = make_tuple(xOr, -origin, yOr + edge);
    auto p2 = make_tuple(xOr, -origin, yOr);
    auto p3 = make_tuple(xOr + edge, -origin, yOr);

    auto p4 = make_tuple(xOr, -origin, yOr + edge);
    auto p5 = make_tuple(xOr + edge, -origin, yOr);
    auto p6 = make_tuple(xOr + edge, -origin, yOr + edge);

    write_triangle(p1, p2, p3, vertexFile);
    write_triangle(p4, p5, p6, vertexFile);

    auto normal = make_tuple(0,-1,0);
    write_triangle(normal,normal,normal,normalFile);
    write_triangle(normal,normal,normal,normalFile);
}

//Draw square in ZX Axis, with y = width of box.
void drawSquareUp(float xOr, float yOr, float edge, float height, ofstream *vertexFile, ofstream *normalFile) {
    auto p1 = make_tuple(xOr + edge, height, yOr);
    auto p2 = make_tuple(xOr, height, yOr);
    auto p3 = make_tuple(xOr, height, yOr + edge);

    auto p4 = make_tuple(xOr + edge, height, yOr + edge);
    auto p5 = make_tuple(xOr + edge, height, yOr);
    auto p6 = make_tuple(xOr, height, yOr + edge);

    write_triangle(p1, p2, p3, vertexFile);
    write_triangle(p4, p5, p6, vertexFile);
    
    auto normal = make_tuple(0,1,0);
    write_triangle(normal,normal,normal,normalFile);
    write_triangle(normal,normal,normal,normalFile);
}

// Desenha um plano a partir dos pontos individuais. 
// De cada ponto, sabe-se o lado de cada quadrado, logo � f�cil desenhar o resto do quadrado.
void drawPlane(float length, float divisions, string name) {
    ofstream vertexFile;
    vertexFile.open(name);

    string normalPath = replace_extension(name, "normal");
    ofstream normalFile;
    normalFile.open(normalPath);

    float increment = length / divisions;
    float len_half = length/2;
    //Draw base and top
    for (float line = -len_half; line < len_half; line = line + increment) {
        for (float collumn = -len_half; collumn < len_half; collumn = collumn + increment) {
            drawSquareUp(line, collumn, increment, 0.0f, &vertexFile, &normalFile);
        }
    }
    vertexFile.close();
    normalFile.close();
}
