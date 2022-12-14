#pragma once
#include "Vector3f.h"
#include "Material.h"

enum class COLOR { RED, GREEN, BLUE };

static COLOR toColor(int colorNum) {
	int n = colorNum % 3;

	switch (n) {
	case 0:
		return COLOR::RED;
	case 1:
		return COLOR::GREEN;
	case 2:
		return COLOR::BLUE;
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
	void setMtlVelocity(Vector4f mtlVelocity);
	Vector4f getMtlVelocity() const;
	void move();
	Material getMTL();
	void setMTL(const Material& m);
	void setAmbient(Vector4f ambient);
	void setColor(COLOR color);
	COLOR getColor() const;
	virtual void draw() const = 0;

protected:
	COLOR color;

	Vector4f mtlVelocity;

	Vector3f center;
	Vector3f velocity;
	Material mtl;
};

