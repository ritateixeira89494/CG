#ifndef __PLANE_H__
#define __PLANE_H__

#include <fstream>

using namespace std;

/*!
  This two functions are used in the design of the box, but they draw the same planes as the necessary in plane design.
  So, they need to be public, and in this file.
*/
void drawSquareUp(float xOr, float yOr, float side, float height, ofstream *file);
void drawSquareDown(float xOr, float yOr, float edge, ofstream *file, float origin);

/*!
    Draw a plane from individual points, line by line.
    His behaviour is described in the report.
*/
void drawPlane(float length, float divisions, string name);

#endif // __PLANE_H__
