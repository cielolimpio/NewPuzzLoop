#include "Loop.h"
#include <ctime>

Loop::Loop() {
	loopPoints.clear();
	startLoopPointIdx = endLoopPointIdx = 0;

	sphereString.clear();
	numOfSpheres = 20;

	state = LoopState::START;
	
	score = 0;
	scoreScale = 1;
}

void Loop::clear() {
	loopPoints.clear();
	startLoopPointIdx = endLoopPointIdx = 0;

	sphereString.clear();
	numOfSpheres = 20;

	state = LoopState::BEGIN;

	score = 0;
	scoreScale = 1;
	createLoop();
}

int Loop::getScore() {
	return score;
}

vector<Sphere> Loop::getSphereString() {
	return sphereString;
}

void Loop::addSphere(int numOfColor) {
	if (numOfSpheres > 0) {
		int colorNum = (int)rand() % numOfColor;
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
	for (int i = -boundaryX - radius * 5; i < -boundaryX - radius * 3; i++)
		loopPoints.push_back(Vector3f(i, height, 0.0f));
	// sphere loop
	startLoopPointIdx = loopPoints.size();

	for (int i = -boundaryX - radius * 3; i < -boundaryX + radius; i++)
		loopPoints.push_back(Vector3f(i, height, 0.0f));

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

bool Loop::finishStarting() {
	if (sphereString.size() > 10) {
		state = LoopState::DEFAULT;
		return true;
	}
	else {
		addSphere(3);
		return false;
	}
}

bool Loop::checkErase(Sphere& sphere, int idx) {
	if (sphereString[idx].getColor() == sphere.getColor()) {
		COLOR color = sphere.getColor();
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
		if (end - start + 2 >= 3) {
			// erase
			handleErasing(start, end);

			Material mtl;
			mtl.setEmission(0.0f, 0.0f, 0.0f, 0.0f);
			mtl.setDiffuse(0.0f, 0.0f, 0.0f, 0.0f);
			mtl.setSpecular(0.0f, 0.0f, 0.0f, 0.0f);
			mtl.setShininess(20.0f);
			Vector4f originalAmbient = sphere.getMTL().getAmbient();
			Vector4f mtlVelocity;
			for (int j = 0; j < 4; j++) {
				mtlVelocity[j] = (0.0f - originalAmbient[j]) / 200.0f;
			}
			Vector4f newAmbient = originalAmbient + mtlVelocity;
			mtl.setAmbient(newAmbient[0], newAmbient[1], newAmbient[2], newAmbient[3]);
			sphere.setMtlVelocity(mtlVelocity);
			sphere.setMTL(mtl);

			sphere.setVelocity(Vector3f(0.0f, 0.0f, 0.0f));
			return true;
		}
	}
	return false;
}

bool Loop::haveToGoBack() {
	if (sphereString[handlingLoopPointIdx].getColor() == sphereString[handlingLoopPointIdx - 1].getColor())
		return true;
	else return false;
}

void Loop::handleErasing(int start, int end) {
	erasingSphereStartIndex = start;
	erasingSphereEndIndex = end;
	for (int i = 0; i < sphereString.size(); i++) {
		sphereString[i].setVelocityOfIdx(0);
	}
	for (int i = start; i <= end; i++) {
		Material mtl;
		mtl.setEmission(0.0f, 0.0f, 0.0f, 0.0f);
		mtl.setDiffuse(0.0f, 0.0f, 0.0f, 0.0f);
		mtl.setSpecular(0.0f, 0.0f, 0.0f, 0.0f);
		mtl.setShininess(20.0f);
		Vector4f originalAmbient = sphereString[i].getMTL().getAmbient();
		Vector4f mtlVelocity;
		for (int j = 0; j < 4; j++) {
			mtlVelocity[j] = (0.0f - originalAmbient[j]) / 200.0f;
		}
		Vector4f newAmbient = originalAmbient + mtlVelocity;
		mtl.setAmbient(newAmbient[0], newAmbient[1], newAmbient[2], newAmbient[3]);
		sphereString[i].setMtlVelocity(mtlVelocity);
		sphereString[i].setMTL(mtl);
	}
}

void Loop::handleErase() {
	sphereString.erase(sphereString.begin() + erasingSphereStartIndex, sphereString.begin() + erasingSphereEndIndex + 1);

	if (sphereString.empty()) {
		state = LoopState::VICTORY;
		return;
	}

	handlingLoopPointIdx = erasingSphereStartIndex;
	if (handlingLoopPointIdx != 0 && handlingLoopPointIdx != sphereString.size()) {
		if (haveToGoBack()) {
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
}

void Loop::handleInsert(Sphere& sphere, int idx) {
	// TODO : handling when collision with first sphere
	float d1 = getDistance(sphere.getCenter(), sphereString[idx].getCenter());
	float d2 = getDistance(sphere.getCenter(), loopPoints[sphereString[idx].getLoopPointIdx() - 1]);

	if (d1 > d2) {
		handlingLoopPointIdx = idx;
		loopPointIdxToCheckErasing = idx + 1;
	}
	else if (idx != 0) {
		handlingLoopPointIdx = idx - 1;
		loopPointIdxToCheckErasing = idx - 1;
	}
	else {
		// idx == 0
		handlingLoopPointIdx = -1;
		loopPointIdxToCheckErasing = -1;
		for (int i = 0; i < sphereString.size(); i++) {
			sphereString[i].setVelocityOfIdx(0);
		}

		Vector3f newVelocity = (loopPoints[sphereString[0].getLoopPointIdx() + 50] - sphere.getCenter()) / 50.0f;
		sphere.setVelocity(newVelocity);
		return;
	}

	for (int i = 0; i <= handlingLoopPointIdx; i++) {
		sphereString[i].setVelocityOfIdx(1);
	}
	for (int i = handlingLoopPointIdx + 1; i < sphereString.size(); i++) {
		sphereString[i].setVelocityOfIdx(0);
	}

	Vector3f newVelocity = (loopPoints[sphereString[handlingLoopPointIdx].getLoopPointIdx()] - sphere.getCenter()) / 50.0f;
	sphere.setVelocity(newVelocity);
}

LoopState Loop::handleCollision(Sphere& sphere, int idx) {
	if (checkErase(sphere, idx)) {
		score += 30;
		scoreScale++;
		state = LoopState::ERASING;
		return LoopState::ERASING;
	}

	// insert
	state = LoopState::INSERT;
	handleInsert(sphere, idx);
	return LoopState::INSERT;
}

LoopState Loop::handleCollision(COLOR color, int idx) {
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
		if (end - start + 1 >= 3) {
			// erase
			score += (end - start + 1) * 10 * scoreScale;
			scoreScale++;
			handleErasing(start, end);
			state = LoopState::ERASING;
			return LoopState::ERASING;
		}
	}
	state = LoopState::DEFAULT;
	for (int i = 0; i < sphereString.size(); i++) {
		sphereString[i].setVelocityOfIdx(1);
	}
	return LoopState::DEFAULT;
}

bool Loop::isSphereInserted(Sphere& sphere) {
	if (handlingLoopPointIdx == sphereString.size() - 1) {
		if (getDistance(sphere.getCenter(), loopPoints[sphereString[handlingLoopPointIdx].getLoopPointIdx() - 50]) < 1) {
			state = LoopState::DEFAULT;
			sphereString.push_back(sphere);
			int loopPointIdx = sphereString[sphereString.size() - 2].getLoopPointIdx();
			sphereString[sphereString.size() - 1].setCenter(loopPoints[loopPointIdx - 50]);
			sphereString[sphereString.size() - 1].setLoopPointIdx(loopPointIdx - 50);
			for (int i = 0; i < sphereString.size(); i++) {
				sphereString[i].setVelocityOfIdx(1);
			}
			return true;
		}
		else return false;
	}

	else if (loopPointIdxToCheckErasing != -1 && loopPointIdxToCheckErasing != sphereString.size()) {
		if (getDistance(sphere.getCenter(), sphereString[loopPointIdxToCheckErasing].getCenter()) <= 50.0f) {
			if (checkErase(sphere, loopPointIdxToCheckErasing)) {
				score += 30;
				scoreScale++;
				state = LoopState::ERASING;
				loopPointIdxToCheckErasing = -1;
				return true;
			}
			else {
				loopPointIdxToCheckErasing = -1;
				return false;
			}
		}
	}

	else if (getDistance(sphere.getCenter(), loopPoints[sphereString[handlingLoopPointIdx + 1].getLoopPointIdx() + 50]) < 4) {
		state = LoopState::DEFAULT;
		sphereString.insert(sphereString.begin() + 1 + handlingLoopPointIdx, sphere);
		for (int i = handlingLoopPointIdx + 1; i >= 0 ; i--) {
			int loopPointIdx = sphereString[i + 1].getLoopPointIdx();
			sphereString[i].setCenter(loopPoints[loopPointIdx + 50]);
			sphereString[i].setLoopPointIdx(loopPointIdx + 50);
		}
		for (int i = 0; i < sphereString.size(); i++) {
			sphereString[i].setVelocityOfIdx(1);
		}
		return true;
	}

	return false;
}

bool Loop::isErasingComplete() {
	if (sphereString[erasingSphereStartIndex].getMTL().getAmbient()[0] <= 0.01) {
		state = LoopState::ERASE;
		handleErase();
		return true;
	}
	else {
		for (int i = erasingSphereStartIndex; i <= erasingSphereEndIndex; i++) {
			Vector4f mtlVelocity = sphereString[i].getMtlVelocity();
			Vector4f originalAmbient = sphereString[i].getMTL().getAmbient();
			Vector4f newAmbient = originalAmbient + mtlVelocity;
			sphereString[i].setAmbient(newAmbient);
		}
		return false;
	}
}

bool Loop::isEraseComplete() {
	if (handlingLoopPointIdx == sphereString.size() || handlingLoopPointIdx == 0) {
		scoreScale = 1;
		state = LoopState::DEFAULT;
		for (int i = 0; i < sphereString.size(); i++) {
			sphereString[i].setVelocityOfIdx(1);
		}
		return true;
	}
	else if (sphereString[handlingLoopPointIdx - 1].getLoopPointIdx() - sphereString[handlingLoopPointIdx].getLoopPointIdx() == 50) {
		LoopState state = handleCollision(sphereString[handlingLoopPointIdx].getColor(), handlingLoopPointIdx);
		if (state == LoopState::ERASING) return false;
		else {
			scoreScale = 1;
			return true;
		}
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

void Loop::setState(LoopState state) {
	this->state = state;
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
	glLineWidth(10.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < loopPoints.size(); i++)
		glVertex3f(loopPoints[i][0], loopPoints[i][1], loopPoints[i][2]);
	glEnd();
}