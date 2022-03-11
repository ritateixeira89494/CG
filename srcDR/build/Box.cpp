#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "Box.h"

float zero = 0.0f;

//Draw square in ZX Axis, with y = higth of box.
void drawSquareUp(float xOr, float yOr, float side, float hight) {
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
}
//Draw square in ZX Axis, with y = 0.
void drawSquareDown(float xOr, float yOr, float side) {
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
}

//Draw square in XY Axis, with z = 0.
void drawSquareXY(float xOr, float yOr, float side) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.0f, 0.8f, 0.8f);
	
	glBegin(GL_TRIANGLES);
	glVertex3f(xOr, yOr, zero);
	glVertex3f(xOr, yOr + side, zero);
	glVertex3f(xOr + side, yOr, zero);
	glEnd();
	
	glColor3f(0.9f, 0.75f, 0.5f);

	glBegin(GL_TRIANGLES);
	glVertex3f(xOr, yOr + side, zero);
	glVertex3f(xOr + side, yOr + side, zero);
	glVertex3f(xOr + side, yOr, zero);
	glEnd();
}

//Draw square in XY Axis, with z = 0.
void drawSquareXY(float xOr, float yOr, float side, float z) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glColor3f(1.0f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLES);
	glVertex3f(xOr, yOr, z);
	glVertex3f(xOr + side, yOr, z);
	glVertex3f(xOr, yOr + side, z);
	glEnd();
	
	glColor3f(0.9f, 0.75f, 0.5f);

	glBegin(GL_TRIANGLES);
	glVertex3f(xOr, yOr + side, z);
	glVertex3f(xOr + side, yOr, z);
	glVertex3f(xOr + side, yOr + side, z);
	glEnd();
}
//Draw square in YZ Axis, with x = 0.
void drawSquareYZ(float yOr, float zOr, float side) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(1.0f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLES);
	glVertex3f(zero, yOr + side, zOr );
	glVertex3f(zero, yOr , zOr);
	glVertex3f(zero, yOr, zOr+side);
	glEnd();

	glColor3f(0.9f, 0.75f, 0.5f);
	
	glBegin(GL_TRIANGLES);
	glVertex3f(zero, yOr, zOr + side);
	glVertex3f(zero, yOr + side, zOr + side);
	glVertex3f(zero, yOr+side, zOr);
	glEnd();
}

//Draw square in YZ Axis, with x = length of square.
void drawSquareYZ(float yOr, float zOr, float side, float x) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(1.0f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLES);
	glVertex3f(x, yOr + side, zOr);
	glVertex3f(x, yOr, zOr + side);
	glVertex3f(x, yOr, zOr);

	glEnd();

	glColor3f(0.9f, 0.75f, 0.5f);

	glBegin(GL_TRIANGLES);
	glVertex3f(x, yOr, zOr + side);
	glVertex3f(x, yOr + side, zOr);
	glVertex3f(x, yOr + side, zOr + side);

	glEnd();
}