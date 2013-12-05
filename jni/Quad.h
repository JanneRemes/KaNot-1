#pragma once
#ifndef QUAD
#define QUAD

#include <Win32toAndroid.h>
#include <Shader.h>
#include <Debug.h>
#include <objLoader.h>
#include <Camera.h>

class Quad
{
public:
	Quad(int H,int W,int D, int X,int Y,int Z);
	void		setPosition(int,int,int);
	void		setPosition(glm::vec3);
	void		move(int,int);
	void		resize(int,int,int);
	void		rotate(float,int,int,int);
	void		rotate(float,glm::vec3);
	void		Draw(float);
	void		setTexture(GLuint);
	void		setShader(Shader*);
	static float*Projection;

	glm::mat4	Rotate;
	glm::mat4	Scaling;
	glm::mat4	Translate;

	Camera*		camera;

	~Quad(void);

private:

	void		GenBuffer();
	float*		Scale;
	float*		Translation;
	int			w,h,d/*,z,x,y,*/;
	glm::vec3	m_pos;
	float*		Data;
	float*		Rotation;
	GLuint		texid,VBO;
	Shader*		shader;
	objLoader	objLoader;
	float**		_data;
	int*		_faces;

	glm::mat4	view;
};

#endif