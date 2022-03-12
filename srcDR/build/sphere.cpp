#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <corecrt_math_defines.h>

#include <iostream>
#include <string>
#include <fstream>


using namespace std;

ofstream sphere3d;


//Draw square in ZX Axis, with y = higth of box.
void drawSquareUpT(float xOr, float yOr, float side, float height) {
	//glutWireCube(side);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(xOr + side, height, yOr);
	sphere3d << "(" << xOr + side << "," << height << "," << yOr << ");";

	glVertex3f(xOr, height, yOr);
	sphere3d << "(" << xOr << "," << height << "," << yOr << ");";
	glVertex3f(xOr, height, yOr + side);
	sphere3d << "(" << xOr << "," << height << "," << yOr + side << ")\n";

	glEnd();

	glColor3f(1.0f, 1.0f, 0.5f);
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(xOr + side, height, yOr + side);
	sphere3d << "(" << xOr + side << "," << height << "," << yOr + side << ");";

	glVertex3f(xOr + side, height, yOr);
	sphere3d << "(" << xOr + side << "," << height << "," << yOr << ");";
	glVertex3f(xOr, height, yOr + side);
	sphere3d << "(" << xOr << "," << height << "," << yOr + side << ")\n";

	glEnd();
}

void drawFaceSphere(float currentalfa, float  proxAlfa, float  currentBeta, float proxBeta, float  radius){
	//Point 1
	float x1 = radius * cos(currentBeta) * sin(currentalfa);
	float y1 = radius * sin(currentBeta);
	float z1 = radius * cos(currentBeta) * cos(currentalfa);

	//Point 2
	float x2 = radius * cos(currentBeta) * sin(proxAlfa);
	float y2 = radius * sin(currentBeta);
	float z2 = radius * cos(currentBeta) * cos(proxAlfa);

	//Point 3
	float x3 = radius * cos(proxBeta) * sin(currentalfa);
	float y3 = radius * sin(proxBeta);
	float z3 = radius * cos(proxBeta) * cos(currentalfa);
	//Point 4
	float x4 = radius * cos(proxBeta) * sin(proxAlfa);
	float y4 = radius * sin(proxBeta);
	float z4 = radius * cos(proxBeta) * cos(proxAlfa);

	// X axis in red

	if (currentBeta > 0 || proxBeta > 0) {
		glVertex3f(x3, y3, z3);
		sphere3d << "(" << x3 << "," << y3 << "," << z3 << ");";
		glVertex3f(x1, y1, z1);
		sphere3d << "(" << x1 << "," << y1 << "," << z1 << ");";
		glVertex3f(x2, y2, z2);
		sphere3d << "(" << x2 << "," << y2 << "," << z2 << ")\n";


		// X axis in red
		glVertex3f(x4, y4, z4);
		sphere3d << "(" << x4 << "," << y4 << "," << z4 << ");";

		glVertex3f(x3, y3, z3);
		sphere3d << "(" << x3 << "," << y3 << "," << z3 << ");";
		glVertex3f(x2, y2, z2);
		sphere3d << "(" << x2 << "," << y2 << "," << z2 << ")\n";
	}
	else {
		glVertex3f(x3, y3, z3);
		sphere3d << "(" << x3 << "," << y3 << "," << z3 << ");";
		glVertex3f(x2, y2, z2);
		sphere3d << "(" << x2 << "," << y2 << "," << z2 << ");";
		glVertex3f(x1, y1, z1);
		sphere3d << "(" << x1 << "," << y1 << "," << z1 << ")\n";


		// X axis in red
		glVertex3f(x4, y4, z4);
		sphere3d << "(" << x4 << "," << y4 << "," << z4 << ");";

		glVertex3f(x2, y2, z2);
		sphere3d << "(" << x2 << "," << y2 << "," << z2 << ");";
		glVertex3f(x3, y3, z3);
		sphere3d << "(" << x3 << "," << y3 << "," << z3 << ")\n";

	}

}

void drawTopSphere(int radius, int slices, int stacks) {
	//Alfa = xOz plano
	float incrementAlfa = 2 * M_PI / slices;
	float currentalfa;
	float zero = 0.0f;
	float proxAlfa = incrementAlfa;
	
	//Beta = Mexer no y
	float incrementBeta =  M_PI / (2 * stacks);
	float currentBeta;
	float proxBeta= incrementBeta;

	for (currentBeta = 0; currentBeta < (M_PI/2); currentBeta+= incrementBeta, proxBeta += incrementBeta) {
		for (currentalfa = 0; currentalfa < 2 * M_PI; currentalfa += incrementAlfa, proxAlfa += incrementAlfa) {
			drawFaceSphere(currentalfa, proxAlfa, currentBeta, proxBeta, radius);
			drawFaceSphere(currentalfa, proxAlfa, -currentBeta, -proxBeta, radius);
		}
	}
}

void drawSphere(int radius, int slices, int stacks, string filename) {
	sphere3d.open(filename + ".3d.txt");

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);

	drawTopSphere(4, 10, 10);
	glEnd();

	sphere3d.close();
}


