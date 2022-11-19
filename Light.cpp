#include "Light.h"
#include <GL/glut.h>

Light::Light(float x, float y, float z, int L_ID) {
	this->lightID = L_ID;
	this->pos[0] = x; this->pos[1] = y; this->pos[1] = z;
	setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
	setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
}

void Light::setAmbient(float r, float g, float b, float a) {
	this->ambient[0] = r;
	this->ambient[1] = g;
	this->ambient[2] = b;
	this->ambient[3] = a;
}

void Light::setDiffuse(float r, float g, float b, float a) {
	this->diffuse[0] = r;
	this->diffuse[1] = g;
	this->diffuse[2] = b;
	this->diffuse[3] = a;
}

void Light::setSpecular(float r, float g, float b, float a) {
	this->specular[0] = r;
	this->specular[1] = g;
	this->specular[2] = b;
	this->specular[3] = a;
}

void Light::draw() const {
	glEnable(lightID);
	glLightfv(lightID, GL_AMBIENT, ambient);
	glLightfv(lightID, GL_DIFFUSE, diffuse);
	glLightfv(lightID, GL_SPECULAR, specular);
	glLightfv(lightID, GL_POSITION, pos);
}