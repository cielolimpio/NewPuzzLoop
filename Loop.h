#pragma once

#include <vector>
using namespace std;

#include "Constants.h"
#include "Sphere.h"

enum class LoopState { DEFAULT, START, BEGIN, INSERT, ERASE, VICTORY, GAME_OVER };

class Loop
{
public:
	Loop();
	void clear();

	int getScore();

	vector<Sphere> getSphereString();

	void addSphere(int numOfColor);
	void createLoop();

	bool finishStarting();

	bool checkErase(Sphere& sphere, int idx);
	bool haveToGoBack();
	void handleErase(int start, int end);
	void handleInsert(Sphere& sphere, int idx);

	LoopState handleCollision(Sphere& sphere, int idx);
	LoopState handleCollision(COLOR color, int idx);

	bool isSphereInserted(Sphere& sphere);
	bool isEraseComplete();

	void moveSphere();
	LoopState getState();
	void setState(LoopState state);

	void draw() const;

private:
	LoopState state;

	int score;

	vector<Vector3f> loopPoints;
	int startLoopPointIdx;
	int endLoopPointIdx;

	int handlingLoopPointIdx;
	int loopPointIdxToCheckErasing;

	vector<Sphere> sphereString;
	int numOfSpheres;
};

