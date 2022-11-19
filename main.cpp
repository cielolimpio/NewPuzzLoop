#include <iostream>
#include <vector>

#include "Sphere.h"
#include "Light.h"
#include "GL/glut.h"

using namespace std;

#define WINDOW_X 200
#define WINDOW_Y 200

#define WINDOW_WIDTH 640		// window's width
#define WINDOW_HEIGHT 640		// window's height

#define boundaryX (WINDOW_WIDTH)/2
#define boundaryY (WINDOW_HEIGHT)/2


vector<Sphere> spheres;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);

void initialize() {
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	Material mtl1;
	mtl1.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl1.setAmbient(0.4f, 0.4f, 0.1f, 1.0f);
	mtl1.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	mtl1.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl1.setShininess(10.0f);

	Material mtl2(mtl1), mtl3(mtl1);
	mtl2.setAmbient(0.1f, 0.4f, 0.4f, 1.0f);
	mtl3.setAmbient(0.4f, 0.1f, 0.4f, 1.0f);

	Sphere sphere1(50, 20, 20);
	sphere1.setCenter(0.0f, -200.0f, 0.0f);
	sphere1.setVelocity(0.02f, 0.06f, 0.0f);
	sphere1.setMTL(mtl1);
	spheres.push_back(sphere1);

	Sphere sphere2(sphere1);
	sphere2.setCenter(100.0f, 200.0f, 0.0f);
	sphere2.setVelocity(-0.06f, -0.05f, 0.0f);
	sphere2.setMTL(mtl2);
	spheres.push_back(sphere2);

	Sphere sphere3(sphere1);
	sphere3.setCenter(-100.0f, 0.0f, 0.0f);
	sphere3.setVelocity(-0.2f, 0.2f, 0.0f);
	sphere3.setMTL(mtl3);
	spheres.push_back(sphere3);
}

bool isCollisionDetected(const Sphere& sph1, const Sphere& sph2) {
	float distanceX = sph1.getCenterX() - sph2.getCenterX();
	float distanceY = sph1.getCenterY() - sph2.getCenterY();
	return sqrt(pow(distanceX, 2.0f) + pow(distanceY, 2.0f)) <= sph1.getRadius() + sph2.getRadius();
}

void handleCollision(Sphere& sph1, Sphere& sph2) {
	if (isCollisionDetected(sph1, sph2)) {
		float distanceX = sph1.getCenterX() - sph2.getCenterX();
		float distanceY = sph1.getCenterY() - sph2.getCenterY();
		float d = pow(distanceX, 2.0f) + pow(distanceY, 2.0f);
		float nx = distanceX / d;
		float ny = distanceY / d;
		float p = sph1.getCenterX() * nx + sph1.getCenterY() * ny - sph2.getCenterX() * nx - sph2.getCenterY() * ny;
		float vx1 = sph1.getVelocityX() + p * nx;
		float vy1 = sph1.getVelocityY() + p * ny;
		float vx2 = sph2.getVelocityX() - p * nx;
		float vy2 = sph2.getVelocityY() - p * ny;

		sph1.setVelocity(vx1, vy1, sph1.getVelocityZ());
		sph2.setVelocity(vx2, vy2, sph2.getVelocityZ());
	}
}

void idle() {
	for (int i = 0; i < spheres.size(); i++) {
		for (int j = i + 1; j < spheres.size(); j++) {
			handleCollision(spheres[i], spheres[j]);
		}
	}

	for (int i = 0; i < spheres.size(); i++) {
		float radius = spheres[i].getRadius();
		const float centerX = spheres[i].getCenterX();
		const float centerY = spheres[i].getCenterY();
		if (centerX + radius >= boundaryX || centerX - radius <= -boundaryX)
			spheres[i].setVelocity(-spheres[i].getVelocityX(), spheres[i].getVelocityY(), spheres[i].getVelocityZ());
		if (centerY + radius >= boundaryY || centerY - radius <= -boundaryY)
			spheres[i].setVelocity(spheres[i].getVelocityX(), -spheres[i].getVelocityY(), spheres[i].getVelocityZ());
		spheres[i].move();
		glutPostRedisplay();
	}

	glutPostRedisplay();
}


void displayCharacters(void* font, string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	light.draw();

	for (int i = 0; i < spheres.size(); i++) {
		switch (i) {
		case 0:
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
		case 1:
			glColor3f(0.0f, 1.0f, 0.0f);
			break;
		case 2:
			glColor3f(0.0f, 0.0f, 1.0f);
			break;
		default:
			glColor3f(0.5f, 0.5f, 0.5f);
			break;
		}
		spheres[i].draw();
	}
	glPopMatrix();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Draw three spheres");
	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
