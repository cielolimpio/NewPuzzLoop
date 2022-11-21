#include"Cannon.h"
#include "Constants.h"

Cannon::Cannon() {
	angle = 0.0f;
	direction[0] = cos(angle * 3.141592 / 180);
	direction[1] = sin(angle * 3.141592 / 180);
	pos[0] =  -150.0f;
	pos[1] =  0.0f;
	pos[2] = 0.0f;
	posOfSphere2 = pos;
	posOfSphere1 = { posOfSphere2[0], posOfSphere2[1]+50, posOfSphere2[2] };
	isPossibleToLaunch = false;
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

COLOR Cannon::setSphereColor(int numOfColor) {
	int colorNum = (int)rand() % numOfColor;
	COLOR color = toColor(colorNum);
	return color;

}

void Cannon::setSpheres() {
	//setting two spheres
		
	Sphere sphere1(25, 30, 30);
	sphere1.setColor(setSphereColor(3));
	sphere1.setCenter(posOfSphere1);
	cannonBall.push_back(sphere1);

	Vector3f di = { direction[0], direction[1], direction[2] };
	cannonBall[0].setVelocity(di);

	Sphere sphere2(25, 30, 30);
	sphere2.setColor(setSphereColor(3));
	sphere2.setCenter(posOfSphere2);
	cannonBall.push_back(sphere2);

	
}

void Cannon::setState(bool state) {
	isPossibleToLaunch = state;
}

bool Cannon::isPossible() {
	return isPossibleToLaunch;
}

Sphere Cannon::launchSpheres() {

	Sphere sphere;
	sphere = cannonBall[0];
	sphere.setCenter(Vector3f(pos[0] + 50 * direction[0], pos[1] + 50 * direction[1], pos[2]));

	cannonBall[0] = cannonBall[1];
	cannonBall[0].setCenter(posOfSphere1);
	Vector3f di = { direction[0], direction[1], direction[2] };
	cannonBall[0].setVelocity(di);

	Sphere sphere2(25, 30, 30);
	sphere2.setColor(setSphereColor(3));
	sphere2.setCenter(posOfSphere2);
	cannonBall[1] = sphere2;

	setState(false);

	Vector3f currentVelocity = sphere.getVelocity();
	sphere.setVelocity(Vector3f(currentVelocity[0] * cannonBallScale, currentVelocity[1] * cannonBallScale, currentVelocity[2] * cannonBallScale));
	return sphere;

}


void Cannon::draw() {
	
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(angle-90, 0.0f, 0.0f, 1.0f);
	glTranslatef(-pos[0], -pos[1], -pos[2]);


	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex2f(-30.0f + pos[0], -60.0f + pos[1]);
	glVertex2f(30.0f + pos[0], -60.0f + pos[1]);
	glVertex2f(30.0f + pos[0], 60.0f + pos[1]);
	glVertex2f(-30.0f + pos[0], 60.0f + pos[1]);
	glEnd();
	
	glEnable(GL_LIGHTING);
	cannonBall[0].draw();
	cannonBall[1].draw();
	
}



