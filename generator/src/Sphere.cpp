#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "Sphere.h"
#include "utils.h"

using namespace std;

//Draw square in ZX Axis, with y = higth of box.
void drawSquareUpT(float xOr, float yOr, float edge, float height, ofstream *file) {
	auto p1 = make_tuple(xOr + edge, height, yOr);
	auto p2 = make_tuple(xOr, height, yOr);
	auto p3 = make_tuple(xOr, height, yOr + edge);

	auto p4 = make_tuple(xOr + edge, height, yOr + edge);
	auto p5 = make_tuple(xOr + edge, height, yOr);
	auto p6 = make_tuple(xOr, height, yOr + edge);

	write_triangle(p1, p2, p3, file);
	write_triangle(p4, p5, p6, file);
}

void drawFaceSphere(float currentalfa, float  proxAlfa, float  currentBeta, float proxBeta, float  radius, ofstream *file){
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

	tuple<float, float, float> p1;
	tuple<float, float, float> p2;
	tuple<float, float, float> p3;
	tuple<float, float, float> p4;
	tuple<float, float, float> p5;
	tuple<float, float, float> p6;

	if (currentBeta > 0 || proxBeta > 0) {
		p1 = make_tuple(x3, y3, z3);
		p2 = make_tuple(x1, y1, z1);
		p3 = make_tuple(x2, y2, z2);

		p4 = make_tuple(x4, y4, z4);
		p5 = make_tuple(x3, y3, z3);
		p6 = make_tuple(x2, y2, z2);
	}
	else {
		p1 = make_tuple(x3, y3, z3);
		p2 = make_tuple(x2, y2, z2);
		p3 = make_tuple(x1, y1, z1);

		p4 = make_tuple(x4, y4, z4);
		p5 = make_tuple(x2, y2, z2);
		p6 = make_tuple(x3, y3, z3);
	}
	write_triangle(p1, p2, p3, file);
	write_triangle(p4, p5, p6, file);
}

void drawTopSphere(int radius, int slices, int stacks, ofstream *file) {
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
			drawFaceSphere(currentalfa, proxAlfa, currentBeta, proxBeta, radius, file);
			drawFaceSphere(currentalfa, proxAlfa, -currentBeta, -proxBeta, radius, file);
		}
	}
}

void drawSphere(int radius, int slices, int stacks, string filename) {
	ofstream file;
	file.open(filename);


	drawTopSphere(radius, slices, stacks/2, &file);

	file.close();
}


