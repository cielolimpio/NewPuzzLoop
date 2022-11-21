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

	bool checkErase(Sphere& sphere, int idx);
	bool willEraseAgain();
	void handleErase(int start, int end);
	void handleInsert(Sphere& sphere, int idx);

	LoopState handleCollision(Sphere& sphere, int idx);
	LoopState handleCollision(COLOR color, int idx);

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
	int loopPointIdxToCheckErasing;

	vector<Sphere> sphereString;
	int numOfSpheres;
};

