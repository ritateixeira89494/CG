#include <GL/glut.h>


#include <stdio.h>
#include <corecrt_math_defines.h>
#include <math.h>



void drawBasePyramid(float radius, int height, int slices, int stacks) {
	float currentRadius;
	float zero = 0.0f;
	float alfa = 2 * M_PI / slices;
	float proxRadius = alfa;
	float y = 0;

	glBegin(GL_TRIANGLES);

	for (currentRadius = 0; currentRadius < 2 * M_PI; currentRadius += alfa, proxRadius += alfa) {
		glColor3f(1.0f, 0.0f, 0.0f);
		// X axis in red
		//Draw triangle in base
		glVertex3f(zero, y, zero);
		glVertex3f(radius * cos(currentRadius), y, radius * sin(currentRadius));
		glVertex3f(radius * cos(proxRadius), y, radius * sin(proxRadius));

	}
	glEnd();

	glutPostRedisplay();
	//    glutSwapBuffers();
}

void drawPyramid(float radius, float height, int slices, float stacks) {
	drawBasePyramid(radius, height, slices, stacks);

	float currentHeight = 0;
	float h = height / stacks;

	float currentRadius = 0;
	float zero = 0.0f;
	float alfa = (2 * M_PI) / slices;
	float proxRadius = alfa;
	//printf("Altura incrementa: %f", h);

	float thisRadio;
	float nextRadio;
	glBegin(GL_TRIANGLES);

	glColor3f(0.0f, 1.0f, 0.0f);
	for (currentRadius = 0; currentRadius < 2 * M_PI; currentRadius += alfa, proxRadius += alfa) {
		for (currentHeight = 0; currentHeight < height; currentHeight += h) {

			thisRadio = ((height - currentHeight) * radius) / height;
			nextRadio = ((height - currentHeight - h) * radius) / height;
			if (nextRadio < 0) nextRadio = 0;
			glVertex3f(thisRadio * cos(proxRadius), currentHeight, thisRadio * sin(proxRadius)); //1
			glVertex3f(thisRadio * cos(currentRadius), currentHeight, thisRadio * sin(currentRadius)); //2
			glVertex3f(nextRadio * cos(proxRadius), currentHeight + h, nextRadio * sin(proxRadius)); //4

			glVertex3f(nextRadio * cos(currentRadius), currentHeight + h, nextRadio * sin(currentRadius)); //3
			glVertex3f(nextRadio * cos(proxRadius), currentHeight + h, nextRadio * sin(proxRadius)); //4
			glVertex3f(thisRadio * cos(currentRadius), currentHeight, thisRadio * sin(currentRadius)); //2


		}

	}

	glEnd();

	glutPostRedisplay();
}
