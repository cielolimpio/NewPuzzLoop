#include "Loop.h"
#include <ctime>

Loop::Loop() {
	loopPoints.clear();
	startLoopPointIdx = endLoopPointIdx = 0;

	sphereString.clear();
	maxNumOfSpheres = 20;

	status = 0;
}

void Loop::addSphere(int numOfColor) {
	if (sphereString.size() < maxNumOfSpheres) {
		srand((unsigned int)time(NULL));
		int colorNum = (int)rand() % numOfColor;
		int n = 2;
		while (n >= 0) {
			colorNum = (int)rand() % numOfColor;
			n--;
		}
		COLOR color = toColor(colorNum);

		if (sphereString.empty() || sphereString.back().getLoopPointIdx() == startLoopPointIdx){
			if (sphereString.size() >= 2) {
				COLOR color1 = sphereString.back().getColor();
				COLOR color2 = (& sphereString.back() - 1)->getColor();
				if (color1 == color2 && color == color1) {
					color = toColor((colorNum + 1) % numOfColor);
				}
			}
			Sphere sphere(25, 30, 30);
			sphere.setColor(color);
			sphere.setLoopPointIdx(0);
			sphere.setCenter(loopPoints[0]);
			sphereString.push_back(sphere);
		}
	}
}

void Loop::createLoop() {
	float radius = 25.0f;
	float height = 150.0f;

	// create loop points
	// start loop
	for (int i = -boundaryX - radius; i < -boundaryX + radius; i++)
		loopPoints.push_back(Vector3f(i, height, 0.0f));
	// sphere loop
	startLoopPointIdx = loopPoints.size();
	for (int i = -boundaryX + radius; i <= boundaryX - radius - emptySpace; i++)
		loopPoints.push_back(Vector3f(i, height, 0.0f));

	for (int i = height; i >= -height; i--)
		loopPoints.push_back(Vector3f(boundaryX - radius - emptySpace, i, 0.0f));

	for (int i = boundaryX - radius - emptySpace; i >= -boundaryX + radius; i--)
		loopPoints.push_back(Vector3f(i, -height, 0.0f));

	endLoopPointIdx = loopPoints.size() - 1;
	// end loop
	for (int i = -boundaryX + radius - 1; i >= -boundaryX - radius; i--)
		loopPoints.push_back(Vector3f(i, -height, 0.0f));

	// set sphere
	addSphere(3);
}

void Loop::moveSphere() {
	if (status == 0) {
		for (int i = 0; i < sphereString.size(); i++) {
			int currLoopPtIdx = sphereString[i].getLoopPointIdx();
			int newLoopPtIdx = currLoopPtIdx + 1;
			sphereString[i].setLoopPointIdx(newLoopPtIdx);
			sphereString[i].setCenter(loopPoints[newLoopPtIdx]);
		}
	}
}

int Loop::checkStatus() {
	if (sphereString.size() == 0) {
		// VICTORY
		status = 1;
	}
	else if (sphereString[0].getLoopPointIdx() == endLoopPointIdx) {
		// GAME OVER
		status = -1;
	}
	return status;
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