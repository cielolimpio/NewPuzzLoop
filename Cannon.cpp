#include"Cannon.h"

Cannon::Cannon() {
	angle = 45.0f;
	direction[0] = cos(angle * 3.141592 / 180);
	direction[1] = sin(angle * 3.141592 / 180);
}

void Cannon::setAngle(float ang) {

	angle = ang;
	direction[0] = cos(angle * 3.141592 / 180);
	direction[1] = sin(angle * 3.141592 / 180);
}

float* Cannon::getDirection() {
	return direction;
}

float Cannon::getAngle() {
	return angle;
}
/*
void Cannon::rotate(int key) {
	switch (key) {
	case -1:
		break;
	case 0:
		if (direction[1] >= 0)
			angle -= 1;
		else if (direction[1] < 0)
			angle += 1;
		break;

	case 1:
		if (direction[1] >= 0)
			angle += 1;
		else if (direction[1] < 0)
			angle -= 1;
		break;

	case 2:
		if (direction[0] >= 0)
			angle -= 1;
		else if (direction[0] < 0)
			angle += 1;
		break;

	case 3:
		if (direction[0] >= 0)
			angle += 1;
		else if (direction[0] < 0)
			angle -= 1;
		break;
	default:
		break;

	}


	//angle+=1;
	//cout<< angle << endl;
	direction[0] = cos(angle*3.141592/180);
	direction[1] = sin(angle*3.141592/180);

	//cout << direction[0] << direction[1] << endl;

	glutPostRedisplay();

}
*/

void Cannon::setSpheres() {
	//setting two spheres
	


}

void Cannon::draw() {
	
	glTranslatef(0, -130.0f, 0);
	glRotatef(angle-90, 0.0f, 0.0f, 1.0f);
	glTranslatef(0,50.0f, 0);


	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex2f(-25.0f, -50.0f);
	glVertex2f(25.0f, -50.0f);
	glVertex2f(25.0f, 50.0f);
	glVertex2f(-25.0f, 50.0f);
	glEnd();
	
}



