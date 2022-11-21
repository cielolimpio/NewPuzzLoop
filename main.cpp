#include <iostream>
#include <string>

#include "Loop.h"
#include "Light.h"
#include "Cannon.h"

Loop loop;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
Cannon cannon;
Sphere sphere;
bool sphereExists = false;

clock_t start_t = clock();
clock_t end_t;

void initialize() {
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	loop.createLoop();
	cannon.setSpheres();
}

bool isCollisionDetected(const Sphere& sph1, const Sphere& sph2) {
	float distanceX = sph1.getCenter()[0] - sph2.getCenter()[0];
	float distanceY = sph1.getCenter()[1] - sph2.getCenter()[1];
	return sqrt(pow(distanceX, 2.0f) + pow(distanceY, 2.0f)) <= sph1.getRadius() + sph2.getRadius();
}

void handleCollision(Sphere& sphere, vector<Sphere>& sphereString) {
	for (int i = 0; i < sphereString.size(); i++) {
		if (isCollisionDetected(sphere, sphereString[i])) {
			if (loop.handleCollision(sphere, i) == LoopState::ERASE)
				sphereExists = false;
			return;
		}
	}
}

void idle() {
	end_t = clock();

	LoopState loopState = loop.getState();

	switch (loopState) {
	case LoopState::DEFAULT:
	{
		if ((float)(end_t - start_t) > 1000 / 40.0f) {
			if (sphereExists == true) {
				float radius = sphere.getRadius();
				const float centerX = sphere.getCenter()[0];
				const float centerY = sphere.getCenter()[1];
				if (centerX >= -boundaryX && centerX <= boundaryX &&
					centerY >= -boundaryY && centerY <= boundaryY) {
					// handle collision between sphere and loop
					vector<Sphere> sphereString = loop.getSphereString();
					handleCollision(sphere, sphereString);
				}
				// when sphere goes out from window
				if (centerX + radius <= -boundaryX || centerX - radius >= boundaryX ||
					centerY + radius <= -boundaryY || centerY - radius >= boundaryY) {
					cannon.setState(true);
				}
			}
			sphere.move();
			loop.moveSphere();

			start_t = end_t;
		}
		break;
	}
	case LoopState::INSERT:
	{
		if ((float)(end_t - start_t) > 1000 / 180.0f) {
			if (loop.isSphereInserted(sphere)) {
				sphereExists = false;
				cannon.setState(true);
			}
				
			sphere.move();
			loop.moveSphere();

			start_t = end_t;
		}
		break;
	}
	case LoopState::ERASE:
	{
		if ((float)(end_t - start_t) > 1000 / 180.0f) {
			if (loop.isEraseComplete())
				cannon.setState(true);
			sphere.move();
			loop.moveSphere();

			start_t = end_t;
		}
		break;
	}
	case LoopState::VICTORY:
		// handle victory
		return;
	case LoopState::GAME_OVER:
		// handle game_over
		return;
	}

	glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y) {
	switch (key)
	{
	case ' ':
		if (cannon.isPossible()) {
			sphere = cannon.launchSpheres();
			sphereExists = true;
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
			float ang = cannon.getAngle() + angleScale;
			cannon.setAngle(ang);
		}
		else if (cannon.getDirection()[1] < 0) {
			float ang = cannon.getAngle() - angleScale;
			cannon.setAngle(ang);
		}
		break;

	case GLUT_KEY_RIGHT:
		if (cannon.getDirection()[1] >= 0) {
			float ang = cannon.getAngle() - angleScale;
			cannon.setAngle(ang);
		}
		else if (cannon.getDirection()[1] < 0) {
			float ang = cannon.getAngle() + angleScale;
			cannon.setAngle(ang);
		}
		break;

	case GLUT_KEY_UP:
		if (cannon.getDirection()[0] >= 0) {
			float ang = cannon.getAngle() + angleScale;
			cannon.setAngle(ang);
		}
		else if (cannon.getDirection()[0] < 0) {
			float ang = cannon.getAngle() - angleScale;
			cannon.setAngle(ang);
		}
		break;

	case GLUT_KEY_DOWN:
		if (cannon.getDirection()[0] >= 0) {
			float ang = cannon.getAngle() - angleScale;
			cannon.setAngle(ang);
		}
		else if (cannon.getDirection()[0] < 0) {
			float ang = cannon.getAngle() + angleScale;
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

	if (sphereExists)
		sphere.draw();

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
