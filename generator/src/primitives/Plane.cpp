#include <fstream>
#include <string>
#include <tuple>
#include "utils/utils.h"

using namespace std;

//Draw square in ZX Axis, with y = 0.
void drawSquareDown(float xOr, float yOr, float edge, ofstream *file, float origin, ofstream &text_file) {
    // Usefull points
    auto p1 = make_tuple(xOr, -origin, yOr + edge); // (0, 1)
    auto p2 = make_tuple(xOr, -origin, yOr); // (0, 0)
    auto p3 = make_tuple(xOr + edge, -origin, yOr); // (1, 0)

    auto p4 = make_tuple(xOr, -origin, yOr + edge); // (0, 1)
    auto p5 = make_tuple(xOr + edge, -origin, yOr); // (1, 0)
    auto p6 = make_tuple(xOr + edge, -origin, yOr + edge); // (1, 1)

    // Texture coordenates
    auto t1 = make_tuple(0, 1);
    auto t2 = make_tuple(0, 0);
    auto t3 = make_tuple(1, 0);

    auto t4 = make_tuple(0, 1);
    auto t5 = make_tuple(1, 0);
    auto t6 = make_tuple(1, 1);

    // Generating the triangles
    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);

    // Generating the texture coordenates
    write_text_triangule(t1, t2, t3, text_file);
    write_text_triangule(t4, t5, t6, text_file);
}

//Draw square in ZX Axis, with y = width of box.
void drawSquareUp(float xOr, float yOr, float edge, float height, ofstream *file, ofstream &text_file) {
    // Usefull points
    auto p1 = make_tuple(xOr + edge, height, yOr); // (1, 0)
    auto p2 = make_tuple(xOr, height, yOr); // (0, 0)
    auto p3 = make_tuple(xOr, height, yOr + edge); // (0, 1)

    auto p4 = make_tuple(xOr + edge, height, yOr + edge); // (1, 1)
    auto p5 = make_tuple(xOr + edge, height, yOr); // (1, 0)
    auto p6 = make_tuple(xOr, height, yOr + edge); // (0, 1)

    // Texture coordenates
    auto t1 = make_tuple(1, 0);
    auto t2 = make_tuple(0, 0);
    auto t3 = make_tuple(0, 1);

    auto t4 = make_tuple(1, 1);
    auto t5 = make_tuple(1, 0);
    auto t6 = make_tuple(0, 1);

    // Generating the triangles
    write_triangle(p1, p2, p3, file);
    write_triangle(p4, p5, p6, file);

    // Generating the texture coordenates
    write_text_triangule(t1, t2, t3, text_file);
    write_text_triangule(t4, t5, t6, text_file);
}

// Desenha um plano a partir dos pontos individuais. 
// De cada ponto, sabe-se o lado de cada quadrado, logo é fácil desenhar o resto do quadrado.
void drawPlane(float length, float divisions, string name) {
    ofstream file;
    file.open(name);

    // Texture file
    ofstream texture_file;
    texture_file.open(name.substr(0, name.length() - 3) + ".text");

    float increment = length / divisions;
    //Draw base and top
    for (float line = 0; line < length; line = line + increment) {
        for (float collumn = 0; collumn < length; collumn = collumn + increment) {
            drawSquareUp(line, collumn, increment, 0.0f, &file, texture_file);
        }
    }
    file.close();
}