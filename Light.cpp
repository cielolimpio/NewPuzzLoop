#include"Light.h"

Light::Light(int x, int y, int z, int id) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	lightID = id;

	for (int i = 0; i < 4; i++) {
		ambient[i] = 0;
		diffuse[i] = 0;
		specular[i] = 0;
	}
}


void Light::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}

void Light::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}

void Light::setSpecular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}

int Light::getLightID() {
	return lightID;
}

void Light::draw() const {
	float am[4] = { ambient[0], ambient[1], ambient[2], ambient[3] };
	float di[4] = { diffuse[0], diffuse[1], diffuse[2], diffuse[3] };
	float sp[4] = { specular[0], specular[1], specular[2], specular[3] };
	float po[3] = { pos[0], pos[1], pos[2]};
	glLightfv(lightID, GL_AMBIENT, am);
	glLightfv(lightID, GL_DIFFUSE, di);
	glLightfv(lightID, GL_SPECULAR, sp);
	glLightfv(lightID, GL_POSITION, po);

}