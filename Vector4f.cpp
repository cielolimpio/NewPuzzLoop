#include "Vector4f.h"

Vector4f::Vector4f() {}
Vector4f::Vector4f(float x, float y, float z, float w) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	pos[3] = w;
}

void Vector4f::setPos(float x, float y, float z, float w) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	pos[3] = w;
}

float& Vector4f::operator[](const int i) {
	return pos[i];
}

float Vector4f::operator[](const int i) const {
	return pos[i];
}

Vector4f operator+(const Vector4f& v1, const Vector4f& v2) {
	return Vector4f(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2], v1[3] + v2[3]);
}


Vector4f operator-(const Vector4f& v1, const Vector4f& v2) {
	return Vector4f(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2], v1[3] - v2[3]);
}


Vector4f operator*(const float s, const Vector4f& v) {
	return Vector4f(s * v[0], s * v[1], s * v[2], s*v[3]);
}

Vector4f operator/(const Vector4f& v, const float s) {
	return Vector4f(v[0] / s, v[1] / s, v[2] / s, v[3] / s);
}

float dotProduct(const Vector4f& v1, const Vector4f& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
}