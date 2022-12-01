#include "Shape3D.h"

void Shape3D::setCenter(const Vector3f& c) {
	center[0] = c[0];
	center[1] = c[1];
	center[2] = c[2];
}

Vector3f Shape3D::getCenter() const { return center; }


void Shape3D::setVelocity(const Vector3f& v) {
	velocity[0] = v[0];
	velocity[1] = v[1];
	velocity[2] = v[2];
}

Vector3f Shape3D::getVelocity() const { return velocity; }

void Shape3D::setMtlVelocity(Vector4f mtlVelocity) {
	this->mtlVelocity = mtlVelocity;
}
Vector4f Shape3D::getMtlVelocity() const {
	return mtlVelocity;
}

Material Shape3D::getMTL() {
	return mtl;
}

void Shape3D::setMTL(const Material& m) {
	mtl.setEmission(m.getEmission()[0], m.getEmission()[1], m.getEmission()[2], m.getEmission()[3]);
	mtl.setAmbient(m.getAmbient()[0], m.getAmbient()[1], m.getAmbient()[2], m.getAmbient()[3]);
	mtl.setDiffuse(m.getDiffuse()[0], m.getDiffuse()[1], m.getDiffuse()[2], m.getDiffuse()[3]);
	mtl.setSpecular(m.getSpecular()[0], m.getSpecular()[1], m.getSpecular()[2], m.getSpecular()[3]);
	mtl.setShininess(m.getShininess());
}

void Shape3D::setAmbient(Vector4f ambient) {
	mtl.setAmbient(ambient[0], ambient[1], ambient[2], ambient[3]);
}

void Shape3D::setColor(COLOR color) {
	mtl.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl.setDiffuse(0.07f, 0.07f, 0.07f, 1.0f);
	mtl.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl.setShininess(20.0f);
	switch (color) {
	case COLOR::RED:
		mtl.setAmbient(0.8f, 0.1f, 0.1f, 1.0f);
		this->color = COLOR::RED;
		break;
	case COLOR::GREEN:
		mtl.setAmbient(0.1f, 0.8f, 0.1f, 1.0f);
		this->color = COLOR::GREEN;
		break;
	case COLOR::BLUE:
		mtl.setAmbient(0.1f, 0.1f, 0.8f, 1.0f);
		this->color = COLOR::BLUE;
		break;
	}
}
COLOR Shape3D::getColor() const { return this->color; }

void Shape3D::move() {
	center[0] = center[0] + velocity[0];
	center[1] = center[1] + velocity[1];
	center[2] = center[2] + velocity[2];
}

