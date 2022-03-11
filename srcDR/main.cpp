
#include <math.h>
#include "main.h"
#include "point.h"

#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "build/Box.cpp"
#include "build/sphere.cpp"
#include "build/Piramide.cpp"

int sizeSquare = 1;
int divisions= 8;

//Camara
float posX = 5;
float posY = 5;
float posZ = 5;

float alpha = 0.7;
float beta = 0.7;
float radiusCamera = 30;


void drawAxis() {
	glBegin(GL_LINES);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(20.0, 0.0, 0.0);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 20.0, 0.0);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 20.0);
	glEnd();
}



// Desenha um plano a partir dos pontos individuais. 
// De cada ponto, sabe-se o lado de cada quadrado, logo é fácil desenhar o resto do quadrado.
void drawPlane(float length, float divisions) {
	float increment = length / divisions;
	printf("Increment original %f", increment);
	//Draw base and top
	for (float line = 0; line < length; line = line + increment) {
		for (float collumn = 0; collumn < length; collumn = collumn+ increment) {
		//	drawSquareUp(line, collumn, increment, length);
			drawSquareDown(line, collumn, increment);
			
			printf("Um quadrado %f", increment);
		}
	}
}

// Desenha um plano a partir dos pontos individuais. 
// De cada ponto, sabe-se o lado de cada quadrado, logo é fácil desenhar o resto do quadrado.
void drawPlaneXY(float length, float divisions) {
	float increment = length / divisions;
	printf("Increment original %f", increment);
	//Draw base and top
	for (float line = 0; line < length; line = line + increment) {
		for (float collumn = 0; collumn < length; collumn = collumn + increment) {
			drawSquareXY(line, collumn, increment);
			drawSquareXY(line, collumn, increment, length);
			printf("Um quadrado %f", increment);
		}
	}
}
// Desenha um plano a partir dos pontos individuais. 
// De cada ponto, sabe-se o lado de cada quadrado, logo é fácil desenhar o resto do quadrado.
void drawPlaneYZ(float length, float divisions) {
	float increment = length / divisions;
	printf("Increment original %f", increment);
	//Draw base and top
	for (float line = 0; line < length; line = line + increment) {
		for (float collumn = 0; collumn < length; collumn = collumn + increment) {
			drawSquareYZ(line, collumn, increment);
			drawSquareYZ(line, collumn, increment, length);
			printf("Um quadrado %f", increment);
		}
	}
}


void drawBox(float length, float divisions) {
	float increment = length / divisions;
	for (float line = 0; line < length; line = line + increment) {

		for (float collumn = 0; collumn < length; collumn = collumn + increment) {
			drawSquareUp(line, collumn, increment, length);
			drawSquareDown(line, collumn, increment);
			drawSquareXY(line, collumn, increment);
			drawSquareXY(line, collumn, increment, length);
			drawSquareYZ(line, collumn, increment);
			drawSquareYZ(line, collumn, increment, length);
			printf("Um quadrado %f", increment);
		}
	}
	//drawPlane(length, divisions);
	//drawPlaneXY(length, divisions);
	//drawPlaneYZ(length, divisions);

}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(radiusCamera * cos(beta) * sin(alpha), radiusCamera * sin(beta), radiusCamera * cos(beta) * cos(alpha),
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);



// put drawing instructions here
	//glutWireTeapot(1);
	//drawPiramide();
	//drawBox(sizeSquare, divisions);
	
	//drawSphere(4, 3, 3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawPyramid(10, 20, 10, 20);
	drawAxis();
	// End of frame
	glutSwapBuffers();
}




// write function to process keyboard events

void processKeys(unsigned char c, int xx, int yy) {

	// put code to process regular keys in here
	switch (c)
	{
	case 'a': alpha += 0.01; break;
	case 's': beta += 0.01; break;
	case 'd': alpha -= 0.01; break;
	case 'w': beta -= 0.01; break;
	case 'q': radiusCamera += 0.1; break;
	case 'e': radiusCamera -= 0.1; break;
	};
	glutPostRedisplay();

}

void lerTeclasEsp(int Key, int x, int y) {
	}




int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(lerTeclasEsp);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
