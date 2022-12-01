#include"Sphere.h"

Sphere::Sphere(float r, int sl, int st) : radius{ r }, slice{ sl }, stack{ st }, loopPointIdx{ 0 }, velocityOfIdx{ 1 } {}

void Sphere::setRadius(float r){
	radius = r;
}

float Sphere:: getRadius() const{
	return radius;
}

void Sphere::setSlice(int sl){
	slice = sl;
}

void Sphere::setStack(int st){
	stack = st;
}

void Sphere::setVelocityOfIdx(int v) {
	velocityOfIdx = v;
}
int Sphere::getVelocityOfIdx() { return velocityOfIdx; }


void Sphere::setLoopPointIdx(int idx) {
	loopPointIdx = idx;
}

int Sphere::getLoopPointIdx() const {
	return loopPointIdx;
}

void Sphere::draw() const {
	glPushMatrix();

	glShadeModel(GL_SMOOTH);

	float em[4] = { mtl.getEmission()[0], mtl.getEmission()[1], mtl.getEmission()[2], mtl.getEmission()[3]};
	float am[4] = { mtl.getAmbient()[0], mtl.getAmbient()[1], mtl.getAmbient()[2], mtl.getAmbient()[3] };
	float di[4] = { mtl.getDiffuse()[0], mtl.getDiffuse()[1], mtl.getDiffuse()[2], mtl.getDiffuse()[3] };
	float sp[4] = { mtl.getSpecular()[0], mtl.getSpecular()[1], mtl.getSpecular()[2], mtl.getSpecular()[3] };
	float sh[1] = { mtl.getShininess() };
	glMaterialfv(GL_FRONT, GL_EMISSION, em);
	glMaterialfv(GL_FRONT, GL_AMBIENT, am);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, di);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sp);
	glMaterialfv(GL_FRONT, GL_SHININESS, sh);
	
	glTranslatef(center[0], center[1], center[2]);

	glutSolidSphere(radius, slice, stack);

	glPopMatrix();
}


