#pragma once

#include <vector>
using namespace std;

#include "Constants.h"
#include "Sphere.h"

class Loop
{
public:
	Loop();

	void addSphere(int numOfColor);
	void createLoop();
	void moveSphere();
	int checkStatus();

	void draw() const;

private:
	int status; // 0: in game, 1: victory, -1: game over

	vector<Vector3f> loopPoints;
	int startLoopPointIdx;
	int endLoopPointIdx;

	vector<Sphere> sphereString;
	int maxNumOfSpheres;
};

