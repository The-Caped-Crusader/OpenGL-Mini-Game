#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<cmath>
#include<Windows.h>
#include <gl/stb_image.h>
#include<gl/glut.h>
float startlimitxl, startlimitxr, End, start, cxl = -0.5, cxr = 0.5, limitxl, limitxr;
int score = 0, squarex = 2, squarey = 2, movex = 1, limitmove = 6, squarex150 = 2, movex150 = 1, limitmove150 = -6;
unsigned int texture;
int width, height, nrChannels;
float angles;
unsigned char* data = NULL;
bool fullScreen = false, flag = true;
float ratio, eyey = -0.3, eyez = 490, eyex, upx, upz = 0;
void background();
void mydraw();
void reshape(int, int);
void timer(int);
void keyboard(unsigned char, int, int);
void specialKeyboard(int, int, int);

void load(int imgnum);
void check(unsigned char* data);

void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN));

	glutCreateWindow("");
	background();
	glutDisplayFunc(mydraw);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);


	glutMainLoop();
}



void background() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);


}


void mydraw() {
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez,
		upx, eyey, upz,
		0, 1, 0);
	glTranslatef(0, 0, -7);

	glEnable(GL_TEXTURE_2D);


	load(5);//side road ground right
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(6, -2, 500);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(12, -2, 500);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(12, -2, 0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(6, -2, 0);
	glEnd();

	load(5); //side road ground left
	//glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-6, -2, 500);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-12, -2, 500);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-12, -2, 0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-6, -2, 0);
	glEnd();

	load(2); //road
	//glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(6, -2, 500);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-6, -2, 500);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-6, -2, 0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(6, -2, 0);
	glEnd();



	load(1); //side-view

	glBegin(GL_QUADS);
	//glColor3f(1, 1, 1);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-10, -2, 500);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-10, 6, 500);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-10, 6, 0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-10, -2, 0);
	glEnd();

	load(1);
	//glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(10, -2, 500);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(10, 6, 500);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(10, 6, 0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(10, -2, 0);
	glEnd();

	load(3); //sky

	glBegin(GL_QUADS);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(10, 6, 500);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-10, 6, 500);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-10, 6, 0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(10, 6, 0);
	glEnd();

	load(4); //end flag

	glBegin(GL_QUADS);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(10, 6, 7);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-10, 6, 7);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-10, -2, 7);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(10, -2, 7);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	//car
	glPushMatrix();
	glTranslatef(0, -1.9, eyez);
	glRotated(angles, 0, 1, 0);
	glBegin(GL_QUADS);
	glColor3f(.2, .8, .9);
	glVertex3f(cxl, 0, -3);
	glVertex3f(cxr, 0, -3);
	glVertex3f(cxr, 0, 1);
	glVertex3f(cxl, 0, 1);

	glColor3f(.2, .8, .9);
	glVertex3f(cxl, 0.2, 0);
	glVertex3f(cxr, 0.2, 0);
	glVertex3f(cxr, 0.2, 1);
	glVertex3f(cxl, 0.2, 1);

	glColor3f(.2, .8, .9);
	glVertex3f(cxl, 0.2, 1);
	glVertex3f(cxr, 0.2, 1);
	glVertex3f(cxr, 0, 1);
	glVertex3f(cxl, 0, 1);

	glColor3f(1, 0, 0);
	glVertex3f(cxl, 0.2, 1);
	glVertex3f(cxl, 0, 1);
	glVertex3f(cxl, 0, 0);
	glVertex3f(cxl, 0.2, 0);

	glColor3f(1, 0, 0);
	glVertex3f(cxr, 0.2, 1);
	glVertex3f(cxr, 0, 1);
	glVertex3f(cxr, 0, 0);
	glVertex3f(cxr, 0.2, 0);

	glColor3f(.2, 0, .9);
	glVertex3f(cxl, 0.4, -1.7);
	glVertex3f(cxr, 0.4, -1.7);
	glVertex3f(cxr, 0.4, -0.5);
	glVertex3f(cxl, 0.4, -0.5);

	glColor3f(.0, .0, 1);
	glVertex3f(cxl, 0.2, 0);
	glVertex3f(cxr, 0.2, 0);
	glVertex3f(cxr, 0.4, -0.5);
	glVertex3f(cxl, 0.4, -0.5);

	glColor3f(.2, 0, .9);
	glVertex3f(cxl, 0.4, -1.7);
	glVertex3f(cxl, 0, -1.7);
	glVertex3f(cxl, 0, -0.5);
	glVertex3f(cxl, 0.4, -0.5);

	glColor3f(.2, 0, .9);
	glVertex3f(cxr, 0.4, -1.7);
	glVertex3f(cxr, 0, -1.7);
	glVertex3f(cxr, 0, -0.5);
	glVertex3f(cxr, 0.4, -0.5);

	glColor3f(.0, .0, 1);
	glVertex3f(cxl, 0.4, -1);
	glVertex3f(cxr, 0.4, -1);
	glVertex3f(cxr, 0.2, -0.5);
	glVertex3f(cxl, 0.2, -0.5);

	glColor3f(.2, .8, .9);
	glVertex3f(cxl, 0.2, -3);
	glVertex3f(cxr, 0.2, -3);
	glVertex3f(cxr, 0.2, -2);
	glVertex3f(cxl, 0.2, -2);

	glColor3f(.2, .8, .9);
	glVertex3f(cxl, 0.2, -2);
	glVertex3f(cxr, 0.2, -2);
	glVertex3f(cxr, 0, -2);
	glVertex3f(cxl, 0, -2);

	glColor3f(1, 0, 0);
	glVertex3f(cxl, 0.2, -2);
	glVertex3f(cxl, 0, -2);
	glVertex3f(cxl, 0, -3);
	glVertex3f(cxl, 0.2, -3);

	glVertex3f(cxl, 0.2, -3);
	glVertex3f(cxl, 0, -3);
	glVertex3f(cxr, 0, -3);
	glVertex3f(cxr, 0.2, -3);

	glVertex3f(cxr, 0.2, -2);
	glVertex3f(cxr, 0, -2);
	glVertex3f(cxr, 0, -3);
	glVertex3f(cxr, 0.2, -3);

	glEnd();

	glPopMatrix();

	//BLOCKS

	glPushMatrix();
	glTranslatef(4, -2.1, 300);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);

	//front
	glVertex3f(0, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(0, 2, 2);

	//back
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(0, 2, -3);

	//left
	glVertex3f(0, 0, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, -3);
	glVertex3f(0, 0, -3);

	//right
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);

	//down
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 0, 2);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, -2.1, 150);

	glBegin(GL_QUADS);
	//front
	glVertex3f(squarex150 - 2, 0, 2);
	glVertex3f(squarex150, 0, 2);
	glVertex3f(squarex150, 2, 2);
	glVertex3f(squarex150 - 2, 2, 2);

	//back
	glVertex3f(squarex150 - 2, 0, -3);
	glVertex3f(squarex150, 0, -3);
	glVertex3f(squarex150, 2, -3);
	glVertex3f(squarex150 - 2, 2, -3);

	//left
	glVertex3f(squarex150 - 2, 0, 2);
	glVertex3f(squarex150 - 2, 2, 2);
	glVertex3f(squarex150 - 2, 2, -3);
	glVertex3f(squarex150 - 2, 0, -3);

	//right
	glVertex3f(squarex150, 0, -3);
	glVertex3f(squarex150, 2, -3);
	glVertex3f(squarex150, 2, 2);
	glVertex3f(squarex150, 0, 2);

	//down
	glVertex3f(squarex150 - 2, 0, 2);
	glVertex3f(squarex150 - 2, 0, -3);
	glVertex3f(squarex150, 0, -3);
	glVertex3f(squarex150, 0, 2);


	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -2.1, 200);

	glBegin(GL_QUADS);
	//front
	glVertex3f(0, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(0, 2, 2);

	//back
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(0, 2, -3);

	//left
	glVertex3f(0, 0, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, -3);
	glVertex3f(0, 0, -3);

	//right
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);

	//down
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 0, 2);


	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, -2.1, 200);

	glBegin(GL_QUADS);
	//front
	glVertex3f(0, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(0, 2, 2);

	//back
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(0, 2, -3);

	//left
	glVertex3f(0, 0, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, -3);
	glVertex3f(0, 0, -3);

	//right
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);

	//down
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 0, 2);


	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-4, -2.1, 350);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	//front
	glVertex3f(0, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(0, 2, 2);

	//back
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(0, 2, -3);

	//left
	glVertex3f(0, 0, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, -3);
	glVertex3f(0, 0, -3);

	//right
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);

	//down
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 0, 2);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, -2.1, 400);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	//front
	glVertex3f(0, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(0, 2, 2);

	//back
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(0, 2, -3);

	//left
	glVertex3f(0, 0, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, -3);
	glVertex3f(0, 0, -3);

	//right
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);

	//down
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 0, 2);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -2.1, 400);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	//front
	glVertex3f(0, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(0, 2, 2);

	//back
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(0, 2, -3);

	//left
	glVertex3f(0, 0, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, -3);
	glVertex3f(0, 0, -3);

	//right
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);

	//down
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 0, 2);

	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -2.1, 270);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	//front
	glVertex3f(0, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(0, 2, 2);

	//back
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(0, 2, -3);

	//left
	glVertex3f(0, 0, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, -3);
	glVertex3f(0, 0, -3);

	//right
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);

	//down
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 0, 2);

	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-4, -2.1, 300);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	//front
	glVertex3f(0, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(0, 2, 2);

	//back
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(0, 2, -3);

	//left
	glVertex3f(0, 0, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, -3);
	glVertex3f(0, 0, -3);

	//right
	glVertex3f(2, 0, -3);
	glVertex3f(2, 2, -3);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);

	//down
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, -3);
	glVertex3f(2, 0, -3);
	glVertex3f(2, 0, 2);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2.1, 70);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	//front
	glVertex3f(squarex - 2, 0, 2);
	glVertex3f(squarex, 0, 2);
	glVertex3f(squarex, 2, 2);
	glVertex3f(squarex - 2, 2, 2);

	//back
	glVertex3f(squarex - 2, 0, -3);
	glVertex3f(squarex, 0, -3);
	glVertex3f(squarex, 2, -3);
	glVertex3f(squarex - 2, 2, -3);

	//left
	glVertex3f(squarex - 2, 0, 2);
	glVertex3f(squarex - 2, 2, 2);
	glVertex3f(squarex - 2, 2, -3);
	glVertex3f(squarex - 2, 0, -3);

	//right
	glVertex3f(squarex, 0, -3);
	glVertex3f(squarex, 2, -3);
	glVertex3f(squarex, 2, 2);
	glVertex3f(squarex, 0, 2);

	//down
	glVertex3f(squarex - 2, 0, 2);
	glVertex3f(squarex - 2, 0, -3);
	glVertex3f(squarex, 0, -3);
	glVertex3f(squarex, 0, 2);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2.1, 450);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	//front
	glVertex3f(squarex - 2, 0, 2);
	glVertex3f(squarex, 0, 2);
	glVertex3f(squarex, 2, 2);
	glVertex3f(squarex - 2, 2, 2);

	//back
	glVertex3f(squarex - 2, 0, -3);
	glVertex3f(squarex, 0, -3);
	glVertex3f(squarex, 2, -3);
	glVertex3f(squarex - 2, 2, -3);

	//left
	glVertex3f(squarex - 2, 0, 2);
	glVertex3f(squarex - 2, 2, 2);
	glVertex3f(squarex - 2, 2, -3);
	glVertex3f(squarex - 2, 0, -3);

	//right
	glVertex3f(squarex, 0, -3);
	glVertex3f(squarex, 2, -3);
	glVertex3f(squarex, 2, 2);
	glVertex3f(squarex, 0, 2);

	//down
	glVertex3f(squarex - 2, 0, 2);
	glVertex3f(squarex - 2, 0, -3);
	glVertex3f(squarex, 0, -3);
	glVertex3f(squarex, 0, 2);

	glEnd();
	glPopMatrix();





	glutSwapBuffers();
}

void reshape(int w, int h) {
	if (h == 0) h = 1;
	ratio = w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 1, 500);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
	glutPostRedisplay();
	glutFullScreen();
	glutTimerFunc(10, timer, 0);
	//score
	if (eyez == 70 || eyez == 350 || eyez == 100 || eyez == 450 || eyez == 270) {
		score++;
	}
	else if (eyez == 200 || eyez == 300 || eyez == 400) {
		score = score + 2;
	}
	//COLLISIONS

	if (eyez >= 347 && eyez <= 355 && ((cxl >= -4 && cxl <= -2) || (cxr >= -4 && cxl <= -2)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}
	else 	if (eyez >= 397 && eyez <= 405 && ((cxr >= 4 && cxr <= 6) || (cxr >= 4 && cxr <= 6)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}
	else 	if (eyez >= 397 && eyez <= 405 && ((cxl >= -2 && cxl <= 0) || (cxr >= -2 && cxr <= 0)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}
	else 	if (eyez >= 267 && eyez <= 275 && ((cxl >= 0 && cxl <= 2) || (cxr >= 0 && cxr <= 2)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}

	else 	if (eyez >= 297 && eyez <= 305 && ((cxl >= -4 && cxl <= -2) || (cxr >= -3 && cxr <= -1)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}
	else 	if (eyez >= 297 && eyez <= 305 && ((cxl >= 4 && cxl <= 6) || (cxr >= 3 && cxr <= 5)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}
	else 	if (eyez >= 67 && eyez <= 75 && ((cxl >= squarex - 2 && cxl <= squarex) || (cxr >= squarex - 2 && cxr <= squarex)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}
	else 	if (eyez >= 447 && eyez <= 455 && ((cxl >= squarex - 2 && cxl <= squarex) || (cxr >= squarex - 2 && cxr <= squarex)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}
	else 	if (eyez >= 147 && eyez <= 155 && ((cxl >= squarex150 && cxl <= squarex150 + 2) || (cxr >= squarex150 && cxr <= squarex150 + 2)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}
	else 	if (eyez >= 197 && eyez <= 205 && ((cxl >= -2 && cxl <= 0) || (cxr >= -2 && cxr <= 0)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}
	else 	if (eyez >= 197 && eyez <= 205 && ((cxl >= 4 && cxl <= 6) || (cxr >= 3 && cxr <= 5)) && flag == true) {
		start = 0;
		std::cout << "Game over \n";
		std::cout << "score: " << score;
		glutHideWindow();
		flag = false;
	}

	//REACH TO THE FLAG
	else {
		End = eyez;
		if (End >= 10) {
			eyez -= start;

		}

		if (eyez == 10 && flag == true) {
			std::cout << "Conglatulations!!" << std::endl;
			std::cout << "score: " << score;
			glutHideWindow();
			flag = false;
			start = 0;
		}


	}
	if (squarex != limitmove && squarex - 2 != limitmove) {
		squarex += movex;

	}
	else {
		limitmove = -limitmove;
		movex = -movex;

	}
	if (squarex150 != limitmove150 && squarex150 + 2 != limitmove150) {
		squarex150 -= movex150;

	}
	else {
		limitmove150 = -limitmove150;
		movex150 = -movex150;

	}

}



//KEYBOARDS

void keyboard(unsigned char key, int x, int y) {
	if (key == 'f') {
		movex = 0;
		movex150 = 0;
	}
	if (key == 'e') {
		glutHideWindow();
	}

	if (key == 's') {


		start = 5;
		startlimitxl = -1;
		startlimitxr = 1;
	}
	if (key == 'r')
	{
		start = 0;
		startlimitxl = 0;
		startlimitxr = 0;
	}


}

void specialKeyboard(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT) {
		if (cxl <= -5) {
			limitxl = 0;
			limitxr = 1;
		}
		else {
			limitxr = startlimitxr;
			limitxl = startlimitxl;
		}

		cxl += limitxl;
		cxr += limitxl;
	}



	if (key == GLUT_KEY_RIGHT) {
		if (cxr >= 5) {
			limitxr = 0;
			limitxl = -1;
		}
		else {
			limitxr = startlimitxr;
			limitxl = startlimitxr;
		}

		cxr += limitxr;
		cxl += limitxr;
	}
}






//LOAD TEXTURES


void load(int imgnum) {
	if (imgnum == 1) {

		data = stbi_load("C:/Users/The_C/Downloads/lab6,7/side-view.JPG", &width, &height, &nrChannels, 0);
		check(data);
	}
	else if (imgnum == 2) {

		data = stbi_load("C:/Users/The_C/Downloads/lab6,7/road.BMP", &width, &height, &nrChannels, 0);
		check(data);
	}
	else if (imgnum == 3) {

		data = stbi_load("C:/Users/The_C/Downloads/lab6,7/sky.JPG", &width, &height, &nrChannels, 0);
		check(data);
	}
	else if (imgnum == 4) {

		data = stbi_load("C:/Users/The_C/Downloads/lab6,7/end_flag.PNG", &width, &height, &nrChannels, 0);
		check(data);
	}
	else if (imgnum == 5) {

		data = stbi_load("C:/Users/The_C/Downloads/lab6,7/end_flag.PNG", &width, &height, &nrChannels, 0);
		check(data);
	}




}

//TEXTURE FORM

void check(unsigned char* data) {
	if (data)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}





