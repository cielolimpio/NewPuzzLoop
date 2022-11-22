#pragma once

#include <iostream>
#include <string>
#include <FreeImage.h>
#include <GL/glut.h>

#include"Constants.h"

using namespace std;

class Texture
{
public:
	Texture();

	FIBITMAP* createBitMap(string filename);
	void generateTexture();
	void initializeTexture(string filename);

	GLuint getTextureID() const;

	void drawSquareWithTexture();

private:
	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;
};

