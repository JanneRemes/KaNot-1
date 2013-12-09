#pragma once
#ifndef Shaders
#define Shaders
#include <Win32toAndroid.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Debug.h>
class Shader
{
public:
	Shader(void);
	GLuint loadShader(GLenum shaderType, const char* pSource);
	GLuint PS,VS,Program, Position, Uv, loc, loc2, loc3, loc4, loc5;
	~Shader(void);
	void setUniformMatrix(const char* name, glm::mat4 matrix);
	void setUniformFloat(const char* name, float value);
	void setUniformVec4(const char* name, glm::vec4 vector4);
};
#endif