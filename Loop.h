#pragma once

#include <vector>
using namespace std;

#include "Sphere.h"
#include "Constants.h"

class Loop
{
public:
	Loop();

	void addSphere();
	void createLoop();
	void moveSphere();

	void draw() const;

private:
	vector<Vector3f> loopPoints;
	int startLoopPointIdx;
	int endLoopPointIdx;

	vector<Sphere> sphereString;
	int maxNumOfSpheres;
};

