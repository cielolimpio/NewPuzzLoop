#include "Loop.h"
#include <ctime>

Loop::Loop() {
	loopPoints.clear();
	startLoopPointIdx = endLoopPointIdx = 0;

	sphereString.clear();
	numOfSpheres = 20;

	state = LoopState::DEFAULT;
}

vector<Sphere> Loop::getSphereString() {
	return sphereString;
}

void Loop::addSphere(int numOfColor) {
	if (numOfSpheres > 0) {
		srand((unsigned int)time(NULL));
		int colorNum = (int)rand() % numOfColor;
		int n = 1;
		while (n >= 0) {
			colorNum = (int)rand() % numOfColor;
			n--;
		}
		COLOR color = toColor(colorNum);
		Sphere sphere(25, 30, 30);
		sphere.setLoopPointIdx(0);
		sphere.setCenter(loopPoints[0]);

		if (sphereString.empty()) {
			sphere.setColor(color);
			sphereString.push_back(sphere);
			numOfSpheres--;
		}
		else if (sphereString.back().getLoopPointIdx() == startLoopPointIdx) {
			if (sphereString.size() >= 2) {
				COLOR color1 = sphereString.back().getColor();
				COLOR color2 = (&sphereString.back() - 1)->getColor();
				if (color1 == color2 && color == color1) {
					color = toColor((colorNum + 1) % numOfColor);
				}
			}
			sphere.setColor(color);

			sphereString.push_back(sphere);
			numOfSpheres--;
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

bool Loop::willEraseAgain() {
	COLOR color = sphereString[handlingLoopPointIdx].getColor();
	int start = handlingLoopPointIdx;
	int end = handlingLoopPointIdx;

	if (sphereString[start].getColor() == color) {
		while (start > 0) {
			if (sphereString[start - 1].getColor() == color)
				start--;
			else break;
		}
	}
	if (sphereString[end].getColor() == color) {
		while (end < sphereString.size() - 1) {
			if (sphereString[end + 1].getColor() == color)
				end++;
			else break;
		}
	}

	if (end - start + 1 >= 3) return true;
	else return false;
}

LoopState Loop::handleCollision(COLOR color, int idx, int offset) {
	if (sphereString[idx].getColor() == color) {
		int start = idx;
		int end = idx;

		if (sphereString[start].getColor() == color) {
			while (start > 0) {
				if (sphereString[start - 1].getColor() == color)
					start--;
				else break;
			}
		}
		if (sphereString[end].getColor() == color) {
			while (end < sphereString.size() - 1) {
				if (sphereString[end + 1].getColor() == color)
					end++;
				else break;
			}
		}
		if (end - start + offset + 1 >= 3) {
			// erase
			sphereString.erase(sphereString.begin() + start, sphereString.begin() + end + 1);
			handlingLoopPointIdx = start;
			if (handlingLoopPointIdx != 0 && handlingLoopPointIdx != sphereString.size()) {
				if (willEraseAgain()) {
					for (int i = 0; i < handlingLoopPointIdx; i++) {
						sphereString[i].setVelocityOfIdx(-1);
					}
					for (int i = handlingLoopPointIdx; i < sphereString.size(); i++) {
						sphereString[i].setVelocityOfIdx(0);
					}
				}
				else {
					for (int i = 0; i < handlingLoopPointIdx; i++) {
						sphereString[i].setVelocityOfIdx(0);
					}
					for (int i = handlingLoopPointIdx; i < sphereString.size(); i++) {
						sphereString[i].setVelocityOfIdx(1);
					}
				}
			}
			state = LoopState::ERASE;
			return LoopState::ERASE;
		}
	}
	
	if (offset == 1) {
		// insert
		state = LoopState::INSERT;

		return LoopState::INSERT;
	}
	else {
		state = LoopState::DEFAULT;
		for (int i = 0; i < sphereString.size(); i++) {
			sphereString[i].setVelocityOfIdx(1);
		}
		return LoopState::DEFAULT;
	}
}

bool Loop::isSphereInserted(Sphere& sphere) {
	return false;
}
bool Loop::isEraseComplete() {
	if (handlingLoopPointIdx == sphereString.size() || handlingLoopPointIdx == 0) {
		state = LoopState::DEFAULT;
		for (int i = 0; i < sphereString.size(); i++) {
			sphereString[i].setVelocityOfIdx(1);
		}
		return true;
	}
	else if (sphereString[handlingLoopPointIdx - 1].getLoopPointIdx() - sphereString[handlingLoopPointIdx].getLoopPointIdx() == 50) {
		LoopState state = handleCollision(sphereString[handlingLoopPointIdx].getColor(), handlingLoopPointIdx);
		if (state == LoopState::ERASE) return false;
		else return true;
	}
	else return false;
}

void Loop::moveSphere() {
	for (int i = 0; i < sphereString.size(); i++) {
		int currLoopPtIdx = sphereString[i].getLoopPointIdx();
		int newLoopPtIdx = currLoopPtIdx + sphereString[i].getVelocityOfIdx();
		sphereString[i].setLoopPointIdx(newLoopPtIdx);
		sphereString[i].setCenter(loopPoints[newLoopPtIdx]);
	}
	addSphere(3);
}

LoopState Loop::getState() {
	if (sphereString.size() == 0) {
		// VICTORY
		state = LoopState::VICTORY;
	}
	else if (sphereString[0].getLoopPointIdx() == endLoopPointIdx) {
		// GAME OVER
		state = LoopState::GAME_OVER;
	}
	return state;
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