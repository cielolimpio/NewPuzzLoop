#pragma once
#include "Vector3f.h"
#include "Material.h"

enum class COLOR { YELLOW, BLUE, PURPLE };

static COLOR getColor(int colorNum) {
	switch (colorNum) {
	case 0:
		return COLOR::YELLOW;
	case 1:
		return COLOR::BLUE;
	case 2:
		return COLOR::PURPLE;
	}
}

class Shape3D
{
public:
	Shape3D() {}
	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;
	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;
	void move();
	void setMTL(const Material& m);
	void setColor(COLOR color);
	virtual void draw() const = 0;

protected:
	COLOR color;

	Vector3f center;
	Vector3f velocity;
	Material mtl;
};

