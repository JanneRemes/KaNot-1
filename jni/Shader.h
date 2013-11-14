#pragma once
#ifndef Shaders
#define Shaders
#include <Win32toAndroid.h>
class Shader
{
public:
	Shader(void);
	GLuint loadShader(GLenum shaderType, const char* pSource);
	GLuint PS,VS,Program, Position, Uv, loc, loc2, loc3, loc4, loc5;
	~Shader(void);
};
#endif