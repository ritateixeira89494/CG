#ifndef __PLANE_H__
#define __PLANE_H__

#include <fstream>

using namespace std;

void drawSquareUp(float xOr, float yOr, float side, float height, ofstream *file);
void drawSquareDown(float xOr, float yOr, float edge, ofstream *file);

void drawPlane(float length, float divisions, string name);

#endif // __PLANE_H__