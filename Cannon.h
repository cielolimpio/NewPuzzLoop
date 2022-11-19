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
	float* getDirection();

private:
	//texture or material
	vector <Sphere> cannonBall;
	float direction[3];
	float angle;
	Vector3f pos;
	Vector3f posOfSphere1;
	Vector3f posOfSphere2;

};