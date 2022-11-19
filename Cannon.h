#pragma once
#include<iostream>
#include <cmath>
#include <vector>
#include "Sphere.h"
#include <GL/glut.h>

using namespace std;

class Cannon {
public:
	Cannon();
	//void rotate(int key);
	void setSpheres();
	void draw();
	void setAngle(float ang);
	float getAngle();
	float* getDirection();

private:
	//texture or material
	vector <Sphere> cannonBall;
	float direction[3];
	float angle;
};