#include "Loop.h"
#include <ctime>

Loop::Loop() {
	loopPoints.clear();
	startLoopPointIdx = endLoopPointIdx = 0;

	sphereString.clear();
	maxNumOfSpheres = 5;
}

void Loop::addSphere(int numOfColor) {
	if (sphereString.size() < maxNumOfSpheres) {
		srand((unsigned int)time(NULL));
		int colorNum = (int)rand() % numOfColor;

		if (sphereString.empty() || sphereString.back().getLoopPointIdx() == startLoopPointIdx){
			printf("%d", colorNum);
			Sphere sphere(25, 30, 30);
			sphere.setColor(getColor(colorNum));
			sphere.setLoopPointIdx(0);
			sphere.setCenter(loopPoints[0]);
			sphereString.push_back(sphere);
		}
	}
}

void Loop::createLoop() {
	float radius = 25.0f;

	// create loop points
	// start loop
	for (int i = -boundaryX - radius; i < -boundaryX + radius; i++)
		loopPoints.push_back(Vector3f(i, 0.0f, 0.0f));
	// sphere loop
	startLoopPointIdx = loopPoints.size();
	for (int i = -boundaryX + radius; i <= boundaryX - radius; i++)
		loopPoints.push_back(Vector3f(i, 0.0f, 0.0f));
	endLoopPointIdx = loopPoints.size() - 1;
	// end loop
	for (int i = boundaryX - radius + 1; i <= boundaryX + radius; i++)
		loopPoints.push_back(Vector3f(i, 0.0f, 0.0f));

	// set sphere
	addSphere(3);
}

void Loop::moveSphere() {
	/* Implement */
	for (int i = 0; i < sphereString.size(); i++) {
		int currLoopPtIdx = sphereString[i].getLoopPointIdx();
		int newLoopPtIdx = currLoopPtIdx == loopPoints.size() - 1 ? 0 : currLoopPtIdx + 1;
		sphereString[i].setLoopPointIdx(newLoopPtIdx);
		sphereString[i].setCenter(loopPoints[newLoopPtIdx]);
	}
	
}

void Loop::draw() const {
	/* Implement */
	// draw sphere
	glEnable(GL_LIGHTING);
	for (int i = 0; i < sphereString.size(); i++) {
		sphereString[i].draw();
	}

	// draw loop
	glDisable(GL_LIGHTING);
	glLineWidth(sphereString[0].getRadius() / 3);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < loopPoints.size(); i++)
		glVertex3f(loopPoints[i][0], loopPoints[i][1], loopPoints[i][2]);
	glEnd();
}