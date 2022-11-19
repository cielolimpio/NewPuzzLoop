#pragma once
class Vector4f
{
public:
	Vector4f();
	Vector4f(float x, float y, float z, float w);
	void setPos(float x, float y, float z, float w);
	float& operator[](const int i);
	float operator[](const int i) const;

private:
	float pos[4];

};

Vector4f operator+(const Vector4f& v1, const Vector4f& v2);
Vector4f operator-(const Vector4f& v1, const Vector4f& v2);
Vector4f operator*(const float s, const Vector4f& v);
Vector4f operator/(const Vector4f& v, const float s);
float dotProduct(const Vector4f& v1, const Vector4f& v2);

