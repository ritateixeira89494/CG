#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include "main.h"
#include <stdio.h>

int transRigth = 0.0f;
int transUP = 0.0f;

int rotateRigth = 0.0f;
int rotateUP = 0.0f;

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

void drawSquare(float xOr, float yOr, float side) {
	//glutWireCube(side);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	printf("Um quadradinho: %f %f %f\n", xOr, yOr, side);
	float zero = 0.0f;
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(xOr + side, zero, yOr);

	glVertex3f(xOr, zero, yOr);
	glVertex3f(xOr, zero, yOr + side);

	glEnd();

	glColor3f(1.0f, 1.0f, 0.5f);
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(xOr + side, zero, yOr + side);

	glVertex3f(xOr + side, zero, yOr);
	glVertex3f(xOr, 0.0f, yOr + side);

	glEnd();
	}

// Desenha um plano a partir dos pontos individuais. 
// De cada ponto, sabe-se o lado de cada quadrado, logo é fácil desenhar o resto do quadrado.
void drawPlane(float length, float divisions) {
	float increment = length / divisions;
	printf("Increment original %f", increment);
	for (float line = 0; line < length; line = line + increment) {
		for (float collumn = 0; collumn < length; collumn = collumn+ increment) {
			drawSquare(line, collumn, increment);
			printf("Um quadrado %f", increment);
		}
	}
}


void drawPiramide(void) {
	int sideSize = 1.0f;
	int zero = 0.0f;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Square
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(zero, 0.0f, sideSize);
	glVertex3f(zero, zero, 0.0f);
	glVertex3f(sideSize, zero,zero);
	glEnd();
	glBegin(GL_TRIANGLES);
	// X axis in red
	glVertex3f(sideSize, 0.0f, 0.0f);
	glVertex3f(sideSize, zero, sideSize);
	glVertex3f(zero, zero, sideSize);
	glEnd();

	float altura = 2.0f;
	//Triangle cá
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(sideSize, 0.0f, sideSize);
	glVertex3f(sideSize/2, altura, sideSize/2);
	glVertex3f(zero, zero, sideSize);
	glEnd();
	//Triangle cá
	glColor3f(1.0f, 1.0f, 0.5f);
	glBegin(GL_TRIANGLES);
	glVertex3f(sideSize, 0.0f, zero);
	glVertex3f(sideSize / 2, altura, sideSize / 2);
	glVertex3f(sideSize, zero, sideSize);
	glEnd();
	//Triangle esq
	glColor3f(0.7f, 0.3f, 0.5f);
	glBegin(GL_TRIANGLES);
	glVertex3f(zero, 0.0f, sideSize);
	glVertex3f(sideSize / 2, altura, sideSize / 2);
	glVertex3f(zero, zero, zero);
	glEnd();
	//Triangle tras
	glColor3f(0.7f, 0.4f, 0.2f);
	glBegin(GL_TRIANGLES);
	glVertex3f(zero, zero, zero);
	glVertex3f(sideSize / 2, altura, sideSize / 2);
	glVertex3f(sideSize, 0.0f, zero);
	glEnd();

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
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put the geometric transformations here
	glTranslatef(transRigth, transUP, 0);
	glRotatef(rotateRigth, 1, 0, 0);
	glRotatef(rotateUP, 0, 1, 0);

// put drawing instructions here
	//glutWireTeapot(1);
	//drawPiramide();
	drawPlane(10, 8);
	drawAxis();
	// End of frame
	glutSwapBuffers();
}




// write function to process keyboard events

void lerTeclas(unsigned char Key, int x, int y)
{
	printf("Leu tecla: %c\n", Key);
	switch (Key)
	{
	case 'a': transRigth--; break;
	case 's': transUP--; break;
	case 'd':  transRigth++; break;
	case 'w': transUP++; break;
	};
	printf("valores: %d  %d \n", transRigth, transUP);
	glutPostRedisplay();	
}

void lerTeclasEsp(int Key, int x, int y) {
	printf("Leu tecla: %c\n", Key);
	switch (Key)
	{
	case GLUT_KEY_LEFT: rotateRigth--; break;
	case GLUT_KEY_RIGHT: rotateRigth++; break;
	case GLUT_KEY_UP: rotateUP++; break;
	case GLUT_KEY_DOWN: rotateUP--; break;
	};
	printf("valores: %d  %d \n", rotateRigth, rotateUP);
	glutPostRedisplay();
}

void frato(int button, int state, int x, int y) {
	transRigth = x/100;
	transUP = y/100;
	glutPostRedisplay();
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
	glutKeyboardFunc(lerTeclas);
	glutSpecialFunc(lerTeclasEsp);
	glutMouseFunc(frato);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
