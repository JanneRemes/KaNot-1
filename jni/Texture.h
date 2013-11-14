#pragma once
#ifndef TEXTURE_H

#define TEXTURE_H
#include <Win32toAndroid.h>
#include <stdlib.h>
class Texture
{
public:
	Texture(void);
	~Texture(void);
	char textureName;
	void loadTexture(const char* textureName);
	//void setTexture();

	//int textureWidth, textureHeight;
	GLuint texture;

private:
	

};

#endif