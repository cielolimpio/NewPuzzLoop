#include <iostream>
#include <string>

#include "Loop.h"
#include "Light.h"
#include "Cannon.h"

Loop loop;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
Cannon cannon;
Sphere sphere;


clock_t start_t = clock();
clock_t end_t;

void initialize() {
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	loop.createLoop();
	cannon.setSpheres(3);
}

void idle() {
	end_t = clock();


	if ((float)(end_t - start_t) > 1000 / 300.0f) {
		loop.checkStatus();
		loop.moveSphere();
		loop.addSphere(3);
		
		start_t = end_t;
	}

	glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y) {
	switch (key)
	{
	case ' ':
		if (cannon.isPossible()) {
			sphere = cannon.launchSpheres();
		}
		break;
		
	default:
		break;
	}
}

void specialKeyDown(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
		if (cannon.getDirection()[1] >= 0) {
			float ang = cannon.getAngle() + 1;
			cannon.setAngle(ang);
		}
		else if (cannon.getDirection()[1] < 0) {
			float ang = cannon.getAngle() - 1;
			cannon.setAngle(ang);
		}
		break;

	case GLUT_KEY_RIGHT:
		if (cannon.getDirection()[1] >= 0) {
			float ang = cannon.getAngle() - 1;
			cannon.setAngle(ang);
		}
		else if (cannon.getDirection()[1] < 0) {
			float ang = cannon.getAngle() + 1;
			cannon.setAngle(ang);
		}
		break;

	case GLUT_KEY_UP:
		if (cannon.getDirection()[0] >= 0) {
			float ang = cannon.getAngle() + 1;
			cannon.setAngle(ang);
		}
		else if (cannon.getDirection()[0] < 0) {
			float ang = cannon.getAngle() - 1;
			cannon.setAngle(ang);
		}
		break;

	case GLUT_KEY_DOWN:
		if (cannon.getDirection()[0] >= 0) {
			float ang = cannon.getAngle() - 1;
			cannon.setAngle(ang);
		}
		else if (cannon.getDirection()[0] < 0) {
			float ang = cannon.getAngle() + 1;
			cannon.setAngle(ang);
		}
		break;

	default:
		break;
	}
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw 3D
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(light.getLightID());

	light.draw();

	glPushMatrix();
	loop.draw();
	glPopMatrix();

	cannon.draw();


	//glDisable(light.getLightID());
	//glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(250, 70);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Move spheres along the loop");
	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(specialKeyDown);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
