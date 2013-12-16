#pragma once
#ifndef ENGINE
#define ENGINE

#include <Win32toAndroid.h>
#include <Texture.h>
#include <Camera.h>
#include <Shader.h>
#include <Keyboard.h>
#include <vector>
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
	float	sine,red,green,blue,testi,snowfade;

	Camera*		camera;
	Shader*		shader;
	Keyboard*	keyboard;

	glm::vec4 color;
};

#endif