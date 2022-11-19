#pragma once
#include "Shape3D.h"


class Sphere : public Shape3D {
public:
	Sphere(){}
	Sphere(float r, int sl, int st);

	void setRadius(float r);
	float getRadius() const;
	void setSlice(int sl);
	void setStack(int st);

	void setLoopPointIdx(int idx);
	int getLoopPointIdx() const;

	virtual void draw() const;

	
private:
	COLOR color;

	float radius;
	int slice;
	int stack;

	int loopPointIdx;
};

