#include "Sphere.h"
#include <GL/glut.h>

Sphere::Sphere(float r, int sl, int st) {
	setRadius(r);
	setSlice(sl);
	setStack(st);

	setMTL(Material());
}

void Sphere::setRadius(float r) {
	this->radius = r;
}
float Sphere::getRadius() const {
	return this->radius;
}

void Sphere::setSlice(int sl) {
	this->slice = sl;
}
void Sphere::setStack(int st) {
	this->stack = st;
}

void Sphere::setCenter(float x, float y, float z) {
	this->center[0] = x;
	this->center[1] = y;
	this->center[2] = z;
}
float Sphere::getCenterX() const { return this->center[0]; }
float Sphere::getCenterY() const { return this->center[1]; }
float Sphere::getCenterZ() const { return this->center[2]; }

void Sphere::setVelocity(float x, float y, float z) {
	this->velocity[0] = x;
	this->velocity[1] = y;
	this->velocity[2] = z;
}
float Sphere::getVelocityX() const { return this->velocity[0]; }
float Sphere::getVelocityY() const { return this->velocity[1]; }
float Sphere::getVelocityZ() const { return this->velocity[2]; }

void Sphere::move() {
	for (int i = 0; i < 3; i++) {
		center[i] += velocity[i];
	}
}
void Sphere::setMTL(const Material& m) {
	this->mtl = m;
}

void Sphere::draw() const {
	glPushMatrix();

	glTranslatef(center[0], center[1], center[2]);

	glutSolidSphere(radius, slice, stack);
	glPopMatrix();

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());
}