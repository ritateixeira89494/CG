#include <fstream>
#include <string>
#include <tuple>
#include "utils.h"

using namespace std;

//Draw square in ZX Axis, with y = 0.
void drawSquareDown(float xOr, float yOr, float edge, ofstream *file, float origin) {
    auto p1 = make_tuple(xOr, -origin, yOr + edge);
    auto p2 = make_tuple(xOr, -origin, yOr);
    auto p3 = make_tuple(xOr + edge, -origin, yOr);

    auto p4 = make_tuple(xOr, -origin, yOr + edge);
    auto p5 = make_tuple(xOr + edge, -origin, yOr);
    auto p6 = make_tuple(xOr + edge, -origin, yOr + edge);
    
    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);
}

//Draw square in ZX Axis, with y = width of box.
void drawSquareUp(float xOr, float yOr, float edge, float height, ofstream *file) {
    auto p1 = make_tuple(xOr + edge, height, yOr);
    auto p2 = make_tuple(xOr, height, yOr);
    auto p3 = make_tuple(xOr, height, yOr + edge);

    auto p4 = make_tuple(xOr + edge, height, yOr + edge);
    auto p5 = make_tuple(xOr + edge, height, yOr);
    auto p6 = make_tuple(xOr, height, yOr + edge);
    
    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);
}

// Desenha um plano a partir dos pontos individuais. 
// De cada ponto, sabe-se o lado de cada quadrado, logo � f�cil desenhar o resto do quadrado.
void drawPlane(float length, float divisions, string name) {
    ofstream file;
    file.open(name);

    float increment = length / divisions;
    //Draw base and top
    for (float line = 0; line < length; line = line + increment) {
        for (float collumn = 0; collumn < length; collumn = collumn + increment) {
            drawSquareUp(line, collumn, increment, 0.0f, &file);
        }
    }
    file.close();
}