#pragma once
#include<iostream>
#include <cmath>
#include <vector>
#include "Sphere.h"
#include "Vector3f.h"
#include <GL/glut.h>

using namespace std;

class Cannon {
public:
	Cannon();
	//void rotate(int key);
	void setSpheres(int numOfColor);
	void draw();
	void setAngle(float ang);
	float getAngle();
	Vector3f getDirection();
	Sphere launchSpheres();
	void setState(bool state);
	bool isPossibleToLaunch();


private:
	bool isPossible;

	vector <Sphere> cannonBall;
	Vector3f direction;
	float angle;
	Vector3f pos;
	Vector3f posOfSphere1;
	Vector3f posOfSphere2;


};