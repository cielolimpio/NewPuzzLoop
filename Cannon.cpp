#include"Cannon.h"

Cannon::Cannon() {
	angle = 45.0f;
	direction[0] = cos(angle * 3.141592 / 180);
	direction[1] = sin(angle * 3.141592 / 180);
}

void Cannon::rotate(int key) {
	switch (key) {
	case 0:
		if (direction[1] >= 0)
			angle-=0.1f;
		else if (direction[1] < 0)
			angle+= 0.1f;
		break;

	case 1:
		if (direction[1] >= 0)
			angle+= 0.1f;
		else if (direction[1] < 0)
			angle-= 0.1f;
		break;
	
	case 2:
		if (direction[0] >= 0)
			angle-= 0.1f;
		else if (direction[0] < 0)
			angle+= 0.1f;
		break;

	case 3:
		if (direction[0] >= 0)
			angle+= 0.1f;
		else if (direction[0] < 0)
			angle-= 0.1f;
		break;
	default:
		break;

	}

	direction[0] = cos(angle*3.141592/180);
	direction[1] = sin(angle*3.141592/180);

	glutPostRedisplay();

}

void Cannon::createCannon() {
	//setting two spheres
	


}

void Cannon::draw() {

	//glPushMatrix();
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex2f(-25.0f, -50.0f);
	glVertex2f(25.0f, -50.0f);
	glVertex2f(25.0f, 50.0f);
	glVertex2f(-25.0f, 50.0f);
	glEnd();
	//glFinish();

	//glPopMatrix();
}



