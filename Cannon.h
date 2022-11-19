#pragma once
#include <cmath>
#include <vector>
#include "Sphere.h"
#include <GL/glut.h>

using namespace std;

class Cannon {
public:
	Cannon();
	void rotate(int key);
	void createCannon();
	void draw();

private:
	//texture or material
	vector <Sphere> cannonBall[2];
	float direction[3];
	float angle;
};