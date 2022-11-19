#include"Cannon.h"

Cannon::Cannon() {
	angle = 0.0f;
	direction[0] = cos(angle * 3.141592 / 180);
	direction[1] = sin(angle * 3.141592 / 180);
	pos[0] =  -150.0f;
	pos[1] =  0.0f;
	pos[2] = 0.0f;
	posOfSphere2 = pos;
	posOfSphere1 = { posOfSphere2[0], posOfSphere2[1]+50, posOfSphere2[2] };
	stateOfLaunch = false;
}

void Cannon::setAngle(float ang) {

	angle = ang;
	direction[0] = cos(angle * 3.141592 / 180);
	direction[1] = sin(angle * 3.141592 / 180);
	cannonBall[0].setVelocity(direction);
}

Vector3f Cannon::getDirection() {
	return direction;
}

float Cannon::getAngle() {
	return angle;
}

void Cannon::setSpheres(int numOfColor) {
	//setting two spheres
	
	int colorNum1 = (int)rand() % numOfColor;
	COLOR color1 = toColor(colorNum1);

	Sphere sphere1(25, 30, 30);
	sphere1.setColor(color1);
	sphere1.setCenter(posOfSphere1);
	cannonBall.push_back(sphere1);

	int colorNum2 = (int)rand() % numOfColor;
	COLOR color2 = toColor(colorNum2);

	Sphere sphere2(25, 30, 30);
	sphere2.setColor(color2);
	sphere2.setCenter(posOfSphere2);
	cannonBall.push_back(sphere2);

	Vector3f di = { direction[1], direction[0], direction[2] };
	cannonBall[0].setVelocity(di);
	
}

void Cannon::setState(bool state) {
	isPossibleToLaunch = state;
}

bool Cannon::isPossible() {
	return isPossibleToLaunch;
}

Sphere Cannon::launchSpheres() {
	setState(false);
}


void Cannon::draw() {
	
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(angle-90, 0.0f, 0.0f, 1.0f);
	glTranslatef(0, 50.0f, 0);


	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex2f(-30.0f, -60.0f);
	glVertex2f(30.0f, -60.0f);
	glVertex2f(30.0f, 60.0f);
	glVertex2f(-30.0f, 60.0f);
	glEnd();
	
	glEnable(GL_LIGHTING);
	glTranslatef(-pos[0], -pos[1], -pos[2]);
	cannonBall[0].draw();
	cannonBall[1].draw();
	
}



