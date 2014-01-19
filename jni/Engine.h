#pragma once
#ifndef ENGINE
#define ENGINE

#include <Win32toAndroid.h>
#include <Texture.h>
#include <Camera.h>
#include <Shader.h>
#include <Keyboard.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//#include <OpenGL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#define WINDOWS_FRAMEWORK

class Quad;

class Engine
{
public:
	Engine();
	~Engine();
	void	fixAspectRatio(float desiredWidth,float desiredHeight, float width, float heigth);
	void	Update();
	void	Draw();
	void	CheckCollision(float obj1_x, float obj2_x, float obj1_y, float obj2_y);
	float  _obj1_x,  _obj2_x,  _obj1_y,  _obj2_y;
	//void printDebug(bool error, const char* format, ...);
	float	Scale, blackBarH, blackBarV;
	int		x,y;

private:

	Texture* texture;
	Texture* texture_octo;
	Texture* texture_ganon;
	Texture* texture_snow;

	GLfloat* GlProjection;
	//GLfloat* GlTranslation;

	Quad*	Quad1;
	Quad*	Quad2;
	Quad*	Quad3;
	
	std::vector<Quad*> snowflakes;

	//GLfloat* Data;
	float	position1;
	float	rotationangle, link_rotate;
	int		positionPhase,colorPhase;
	float	sine,red,green,blue,testi,snowfade,snowspawn,falling;

	float randPosX();
	float randPosY();
	float randomMultp();
	float randomi;
	int snowCount;

	Camera*		camera;
	Shader*		shader;
	Keyboard*	keyboard;

	glm::vec4 color;
	glm::vec4 linkcolor;
};

#endif