#pragma once
#ifndef ENGINE
#define ENGINE

#include <Win32toAndroid.h>
#include <Texture.h>
//#include <OpenGL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#define WINDOWS_FRAMEWORK

class Shader;
class Quad;

class Engine
{
public:
	Engine();
	~Engine();
	void fixAspectRatio(float desiredWidth,float desiredHeight, float width, float heigth);
	void Update();
	void Draw();
	//void printDebug(bool error, const char* format, ...);
	float Scale, blackBarH, blackBarV;
	int x,y;

private:

	Texture* texture;
	Texture* texture_octo;
	Texture* texture_ganon;

	GLfloat* GlProjection;
	//GLfloat* GlTranslation;

	//Shader* shader;
	//Shader* shader2;

	Quad* Quad1;
	Quad* Quad2;
	Quad* Quad3;

	//GLfloat* Data;
	float position1;
	float rotation_ganon;
	int positionPhase;
	float sine;

	//GLuint Texture1;
	//unsigned int num_vertices;
};

#endif