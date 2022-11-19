#pragma once

#include <vector>
using namespace std;

#include "Constants.h"
#include "Sphere.h"

enum class LoopState { DEFAULT, INSERT, ERASE, VICTORY, GAME_OVER };

class Loop
{
public:
	Loop();

	vector<Sphere> getSphereString();

	void addSphere(int numOfColor);
	void createLoop();

	bool willEraseAgain();

	LoopState handleCollision(COLOR color, int idx, int offset = 0);

	bool isSphereInserted(Sphere& sphere);
	bool isEraseComplete();

	void moveSphere();
	LoopState getState();

	void draw() const;

private:
	LoopState state;

	vector<Vector3f> loopPoints;
	int startLoopPointIdx;
	int endLoopPointIdx;
	int handlingLoopPointIdx;

	vector<Sphere> sphereString;
	int numOfSpheres;
};

