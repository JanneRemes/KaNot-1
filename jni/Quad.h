#pragma once
#ifndef QUAD
#define QUAD
#include <Win32toAndroid.h>
class Shader;
class Quad
{
public:
	Quad(int,int,int,int);
	void move(int,int);
	void resize (int,int);
	void rotate(float);
	void Draw(float);
	void setTexture(GLuint);
	void setShader(Shader*);
	static float*Projection;

	~Quad(void);

private:

	void GenBuffer();
	float* Scale;
	float* Translation;
	int x,y,w,h;
	float* Data;
	float* Rotation;
	GLuint texid,VBO;
	Shader* shader;
};

#endif