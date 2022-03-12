#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
//#include "Box.h"

using namespace std;

ofstream box3d;
ofstream plane3d;

float zero = 0.0f;

//Draw square in ZX Axis, with y = higth of box.
void drawSquareUp(float xOr, float yOr, float side, float hight, int pB) {
	//glutWireCube(side);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(xOr + side, hight, yOr);

	glVertex3f(xOr, hight, yOr);
	glVertex3f(xOr, hight, yOr + side);

	glEnd();

	glColor3f(1.0f, 1.0f, 0.5f);
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(xOr + side, hight, yOr + side);

	glVertex3f(xOr + side, hight, yOr);
	glVertex3f(xOr, hight, yOr + side);

	glEnd();

	if (pB == 0) {
		plane3d << "(" << xOr + side << "," << hight << "," << yOr << ");";
		plane3d << "(" << xOr << "," << hight << "," << yOr << ");";
		plane3d << "(" << xOr << "," << hight << "," << yOr + side << ")\n";

		plane3d << "(" << xOr + side << "," << hight << "," << yOr + side << ");";
		plane3d << "(" << xOr + side << "," << hight << "," << yOr << ");";
		plane3d << "(" << xOr << "," << hight << "," << yOr + side << ")\n";
	}
	else {
		box3d << "(" << xOr + side << "," << hight << "," << yOr << ");";
		box3d << "(" << xOr << "," << hight << "," << yOr << ");";
		box3d << "(" << xOr << "," << hight << "," << yOr + side << ")\n";

		box3d << "(" << xOr + side << "," << hight << "," << yOr + side << ");";
		box3d << "(" << xOr + side << "," << hight << "," << yOr << ");";
		box3d << "(" << xOr << "," << hight << "," << yOr + side << ")\n";
	}
}
//Draw square in ZX Axis, with y = 0.
void drawSquareDown(float xOr, float yOr, float side, int pB) {
	//glutWireCube(side);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(xOr, zero, yOr + side);
	glVertex3f(xOr, zero, yOr);
	glVertex3f(xOr + side, zero, yOr);
	glEnd();

	glColor3f(1.0f, 1.0f, 0.5f);
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(xOr, zero, yOr + side);
	glVertex3f(xOr + side, zero, yOr);
	glVertex3f(xOr + side, zero, yOr + side);
	glEnd();

	if (pB == 0) {
		plane3d << "(" << xOr << "," << zero << "," << yOr + side << ");";
		plane3d << "(" << xOr << "," << zero << "," << yOr << ");";
		plane3d << "(" << xOr + side << "," << zero << "," << yOr << ")\n";

		plane3d << "(" << xOr << "," << zero << "," << yOr + side << ");";
		plane3d << "(" << xOr + side << "," << zero << "," << yOr << ");";
		plane3d << "(" << xOr + side << "," << zero << "," << yOr + side << ")\n";
	}
	else {
		box3d << "(" << xOr << "," << zero << "," << yOr + side << ");";
		box3d << "(" << xOr << "," << zero << "," << yOr << ");";
		box3d << "(" << xOr + side << "," << zero << "," << yOr << ")\n";

		box3d << "(" << xOr << "," << zero << "," << yOr + side << ");";
		box3d << "(" << xOr + side << "," << zero << "," << yOr << ");";
		box3d << "(" << xOr + side << "," << zero << "," << yOr + side << ")\n";

	}
}

//Draw square in XY Axis, with z = 0.
void drawSquareXY(float xOr, float yOr, float side) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.0f, 0.8f, 0.8f);
	
	glBegin(GL_TRIANGLES);
	glVertex3f(xOr, yOr, zero);
	box3d << "(" << xOr << "," << yOr << "," << zero << ");";
	glVertex3f(xOr, yOr + side, zero);
	box3d << "(" << xOr << "," << yOr + side << "," << zero << ");";
	glVertex3f(xOr + side, yOr, zero);
	box3d << "(" << xOr + side << "," << yOr << "," << zero << ")\n";
	glEnd();
	
	glColor3f(0.9f, 0.75f, 0.5f);

	glBegin(GL_TRIANGLES);
	glVertex3f(xOr, yOr + side, zero);
	box3d << "(" << xOr << "," << yOr + side << "," << zero << ");";
	glVertex3f(xOr + side, yOr + side, zero);
	box3d << "(" << xOr + side << "," << yOr + side << "," << zero << ");";
	glVertex3f(xOr + side, yOr, zero);
	box3d << "(" << xOr + side << "," << yOr << "," << zero << ")\n";
	glEnd();
}

//Draw square in XY Axis, with z = 0.
void drawSquareXY(float xOr, float yOr, float side, float z) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glColor3f(1.0f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLES);
	glVertex3f(xOr, yOr, z);
	box3d << "(" << xOr << "," << yOr << "," << z << ");";
	glVertex3f(xOr + side, yOr, z);
	box3d << "(" << xOr + side << "," << yOr << "," << z << ");";
	glVertex3f(xOr, yOr + side, z);
	box3d << "(" << xOr << "," << yOr + side << "," << z << ")\n";
	glEnd();
	
	glColor3f(0.9f, 0.75f, 0.5f);

	glBegin(GL_TRIANGLES);
	glVertex3f(xOr, yOr + side, z);
	box3d << "(" << xOr << "," << yOr + side << "," << z << ");";
	glVertex3f(xOr + side, yOr, z);
	box3d << "(" << xOr + side << "," << yOr << "," << z << ");";
	glVertex3f(xOr + side, yOr + side, z);
	box3d << "(" << xOr + side << "," << yOr + side << "," << z << ")\n";
	glEnd();
}
//Draw square in YZ Axis, with x = 0.
void drawSquareYZ(float yOr, float zOr, float side) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(1.0f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLES);
	glVertex3f(zero, yOr + side, zOr );
	box3d << "(" << zero << "," << yOr + side << "," << zOr << ");";
	glVertex3f(zero, yOr , zOr);
	box3d << "(" << zero << "," << yOr << "," << zOr << ");";
	glVertex3f(zero, yOr, zOr+side);
	box3d << "(" << zero << "," << yOr << "," << zOr + side << ")\n";
	glEnd();

	glColor3f(0.9f, 0.75f, 0.5f);
	
	glBegin(GL_TRIANGLES);
	glVertex3f(zero, yOr, zOr + side);
	box3d << "(" << zero << "," << yOr << "," << zOr + side << ");";
	glVertex3f(zero, yOr + side, zOr + side);
	box3d << "(" << zero << "," << yOr + side << "," << zOr + side << ");";
	glVertex3f(zero, yOr+side, zOr);
	box3d << "(" << zero << "," << yOr + side << "," << zOr << ")\n";
	glEnd();
}

//Draw square in YZ Axis, with x = length of square.
void drawSquareYZ(float yOr, float zOr, float side, float x) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(1.0f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLES);
	glVertex3f(x, yOr + side, zOr);
	box3d << "(" << x << "," << yOr << "," << zOr << ");";
	glVertex3f(x, yOr, zOr + side);
	box3d << "(" << x << "," << yOr << "," << zOr + side << ");";
	glVertex3f(x, yOr, zOr);
	box3d << "(" << x << "," << yOr << "," << zOr << ")\n";

	glEnd();

	glColor3f(0.9f, 0.75f, 0.5f);

	glBegin(GL_TRIANGLES);
	glVertex3f(x, yOr, zOr + side);
	box3d << "(" << x << "," << yOr << "," << zOr + side << ");";
	glVertex3f(x, yOr + side, zOr);
	box3d << "(" << x << "," << yOr + side << "," << zOr << ");";
	glVertex3f(x, yOr + side, zOr + side);
	box3d << "(" << x << "," << yOr + side << "," << zOr + side << ")\n";

	glEnd();
}


// Desenha um plano a partir dos pontos individuais. 
// De cada ponto, sabe-se o lado de cada quadrado, logo é fácil desenhar o resto do quadrado.
void drawPlane(float length, float divisions, string name) {
	plane3d.open(name + ".3d.txt");

	float increment = length / divisions;
	//Draw base and top
	for (float line = 0; line < length; line = line + increment) {
		for (float collumn = 0; collumn < length; collumn = collumn + increment) {
			drawSquareUp(line, collumn, increment, length, 0);
			//	drawSquareDown(line, collumn, increment, 0);
		}
	}
	plane3d.close();
}


void drawBox(float length, float divisions, string nameOfFile) {
	box3d.open(nameOfFile + ".3d.txt");

	float increment = length / divisions;
	for (float line = 0; line < length; line = line + increment) {

		for (float collumn = 0; collumn < length; collumn = collumn + increment) {
			drawSquareUp(line, collumn, increment, length, 1); //1 -> Box, 0-> Plane
			drawSquareDown(line, collumn, increment, 1); //1 -> Box, 0-> Plane
			drawSquareXY(line, collumn, increment);
			drawSquareXY(line, collumn, increment, length);
			drawSquareYZ(line, collumn, increment);
			drawSquareYZ(line, collumn, increment, length);
		}
	}
	//drawPlane(length, divisions);
	//drawPlaneXY(length, divisions);
	//drawPlaneYZ(length, divisions);

}