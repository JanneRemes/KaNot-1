#include <Engine.h>
#include <stdlib.h>
#include <FileReader.h>
#include <cmath>
#include <Windows.h>
#include <time.h>

#include <Quad.h>
//#include <Windows.h>
#include <iostream>

#undef isnan

Engine::Engine()
{
	Scale = blackBarH = blackBarV = 0;

	x = y			= 0;
	position1		= 0;
	positionPhase	= 0;
	rotationangle	= 0;
	snowfade		= 0;
	snowspawn		= 0;

	isOctoDead = false;

	//Make link texture
	texture =	new Texture();
	texture->loadTexture("Link2.tga");

	//Make octorock texture
	texture_octo = new Texture();
	texture_octo->loadTexture("Octo.tga");

	//Make ganon texture
	texture_ganon = new Texture();
	texture_ganon->loadTexture("Ganon.tga");

	texture_snow = new Texture();
	texture_snow->loadTexture("snow.tga");

	shader =	new Shader();
	camera =	new Camera();
	keyboard =	new Keyboard();

	static float angle = 0.0f;
	angle += 0.5f;

	//Draw texture 1
	Quad1 =	new Quad(128,128,0,100,100,0);
	Quad1->setShader(shader);
	Quad1->setTexture(texture_octo->texture);

	//Draw texture 2
	Quad2 = new Quad(150,150,0,100,100,0);
	Quad2->setShader(shader);
	Quad2->setTexture(texture->texture);

	//Draw texture 3
	Quad3 = new Quad(300,300,0,0,0,0);
	Quad3->setShader(shader);
	Quad3->setTexture(texture_ganon->texture);


	sine		= 0;
	position1	= 0;
	link_rotate = 0;

	red = 0;
	blue = 1;
	green = 0;
	colorPhase = 0;
	snowfade = 1;
	falling = 1;
	snowCount = 50;

	linkcolor = glm::vec4(1,1,1,1);

}

Engine::~Engine()
{
	//Delete always pointers! If there is "new Thing()" -> delete it.
	delete	texture;
	delete	texture_octo;
	delete	texture_ganon;
	delete	Quad1;
	delete	Quad2;
	delete	Quad3;

	for(int i = 0;snowflakes.size() >= snowCount;i++)
	{
		delete snowflakes[i];
	}


}

void Engine::Update()
{
	rotationangle += 1;

	for(int i = 0;snowflakes.size() <= snowCount;i++)
	{
		snowspawn = 100+(i*100);
		snowflakes.push_back(new Quad(24,24,0,randPosX(),700-(i*randomMultp()),0));
		snowflakes[i]->setShader(shader);
		snowflakes[i]->setTexture(texture_snow->texture);
		snowflakes[i]->_speed = randomMultp();
	}

	for(int i = 0; i <= snowCount; i++)
	{
		snowflakes[i]->move(0,-1*(1+snowflakes[i]->_speed));
		snowflakes[i]->rotate(rotationangle*10,0,0,1);
		snowflakes[i]->_opacity -=0.004f;
		snowflakes[i]->setOpacity(snowflakes[i]->getOpacity());

		if(snowflakes[i]->getY() <= 0)
		{
			snowflakes[i]->setPosition(randPosX(),700-(i*randomMultp()),0);
			snowfade = 1.0f;
			snowflakes[i]->_opacity =1.0f;
			snowflakes[i]->_speed = randomMultp();
			
		}
	}

	//Octo
	if(isOctoDead)
	{

	}
	else
	{
		Quad1->setPosition(sin(rotationangle/15)*100+600, cos(rotationangle/15)*100+400,0);
		Quad1->rotate(rotationangle,0,0,1);
	}
	//Link
	//Quad2->setPosition(rotationangle,0,0);
	//Ganon
	Quad3->setPosition(800,250,0);
	Quad3->resize(abs(sin(rotationangle/50))*120,abs(sin(rotationangle/50)*120),0);
	Quad3->rotate(rotationangle,0,0,-1);

	if(GetAsyncKeyState(VK_UP))
	{
		Quad2->move(0,5);
	}
	if(GetAsyncKeyState(VK_DOWN))
	{
		Quad2->move(0,-5);
	}
	if(GetAsyncKeyState(VK_LEFT))
	{
		Quad2->move(-5,0);
	}
	if(GetAsyncKeyState(VK_RIGHT))
	{
		Quad2->move(5,0);
	}
	if(GetAsyncKeyState(VK_SPACE))
	{
		link_rotate += 50;
		Quad2->rotate(link_rotate,0,0,1);
	}
	else
	{
		link_rotate = 0;
		Quad2->rotate(link_rotate,0,0,1);
	}

	if(colorPhase == 0)
	{
		blue -= 0.5f/10;
		red += 0.5f/10;
		if(red >= 1)
			colorPhase++;
	}
	if(colorPhase == 1)
	{
		green += 0.5f/10;
		red -= 0.5f/10;
		if(red <= 0)
			colorPhase++;
	}
	if(colorPhase == 2)
	{	
		blue += 0.5f/10;
		green -= 0.5f/10;
		if(blue >= 1)
			colorPhase = 0;
	}
	color = glm::vec4(red,blue,green,1);

	//Quad2->setColor(glm::vec4(1,1,1,1));

	CheckCollision(Quad2->getX(), Quad1->getX(), Quad1->getY(), Quad2->getY()); 

}

	/**
	*  This code fixes the aspect ration.
	*/
void Engine::fixAspectRatio(float desiredWidth, float desiredHeight, float width, float height)
{
	//////////////////Don't change anything, until its really really necessary!/////////////////////////

	//Calculate desired Aspect Ratio
	float dAR = desiredWidth/desiredHeight;

	//Calculate real Aspect Ratio
	float rAR = width/height;
	float w,h;
	//check Aspect Ratio's
	if(dAR == rAR)
	{
		//Same aspect, no letterboxing needed!
		Scale = width/desiredWidth;
	}
	else if(dAR<rAR)
	{
		//Horizontal letterboxing needed!
		Scale = height/desiredHeight;
		blackBarH = (width-Scale*desiredWidth)/2;
	}
	else
	{
		//Vertical letterboxing needed!
		Scale = width/desiredWidth;
		blackBarV = (height-(Scale*desiredHeight))/2;
	}
	w = desiredWidth*Scale;
	h = desiredHeight*Scale;

	glViewport((int)blackBarH, (int)blackBarV, (int)w, (int)h); // Sets up the OpenGL viewport
	
	checkGlError("ennen setuniformia");
	shader->setUniformMatrix("matProjection",camera->Projection);
	checkGlError("setuniformi projection");
	shader->setUniformMatrix("View",camera->View);
	checkGlError("setuniformi view");

}


void Engine::Draw()
{
	checkGlError("Engine draw");
	//Draw
	glClearColor(0.3f,0.5f,0.3f,1);
	#ifndef ANDROID_FRAMEWORK
	glClearDepth(1);
	#else
	glClearDepthf(1);
	#endif
	//Important GL draw clear thing
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//Quad draws goes here. Remember the draw order.
	Quad1->setColor(color);
	Quad1->Draw(0.8f);
	Quad3->setColor(glm::vec4(1,1,1,1));
	Quad3->Draw(0.9f);
	Quad2->setColor(linkcolor);
	Quad2->Draw(0.7f);

	for(int i = 0; i <= snowCount; i++)
	{
		snowflakes[i]->setColor(glm::vec4(1,1,1,snowflakes[i]->getOpacity()));
		snowflakes[i]->Draw(0.9f);
	}
}

float Engine::randPosX()
{
	randomi = rand()%1280;
	//srand(time(NULL));
	return randomi;
}

float Engine::randomMultp()
{
	randomi = rand()%10;
	//srand(time(NULL));
	return randomi;
}


void Engine::CheckCollision(float obj1_x, float obj2_x, float obj1_y, float obj2_y)
{
	_obj1_x = obj1_x;
	_obj2_x = obj2_x;
	_obj1_y = obj1_y;
	_obj2_y = obj2_y;
	
	if(_obj2_x + 25  >= _obj1_x - 25 &&
		_obj2_x - 25  <= _obj1_x + 25 &&
		_obj2_y + 25  >= _obj1_y - 25 &&
		_obj2_y - 25  <= _obj1_y + 25)
	{
		if(GetAsyncKeyState(VK_SPACE))
		{
			isOctoDead = true;
			Quad1->move(1000,1000);
		}
		if(_obj2_x + 5  >= _obj1_x - 5)
		{
			Quad2->move(-2,0);
		}
		else if(_obj2_x + 5  <= _obj1_x - 5)
		{
			Quad2->move(2,0);
		}
		if(_obj2_y + 5  >= _obj1_y - 5)
		{
			Quad2->move(0,2);
		}
		else if(_obj2_y + 5  <= _obj1_y - 5)
		{
			Quad2->move(0,-2);
		}

		Quad2->rotate(10,glm::vec3(0,0,1));
		//Quad2->move(100,0);
		linkcolor = glm::vec4(1,0,0,1);
	}
	else
	{
		linkcolor = glm::vec4(1,1,1,1);
	}
/* &&
		_obj1_x - 20 < _obj2_x + 20 &&
		_obj1_y + 20 > _obj2_y - 20 &&
		_obj1_y - 20 < _obj2_y + 20*/
}