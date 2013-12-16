#include <Quad.h>
#include <cmath>
#include <stdlib.h>

float* Quad::Projection = NULL;

Quad::Quad(int H,int W,int D, int X,int Y,int Z)
{
	checkGlError("Quad tehty");

	w=W;
	h=H;
	d=D;
	_speed = 1;

	glGenBuffers(1,&VBO);
	checkGlError("glGenBuffers");

	GenBuffer();
	setPosition(X,Y,Z);

	resize(w,h,d);
	Rotate = glm::mat4(1.0f);

	camera = new Camera();

}

void Quad::GenBuffer()
{
	checkGlError("Quad Buffer");

	float* Data = (float*)malloc(30*sizeof(float));

	Data[0] = -0.5f; 
    Data[1] = -0.5f; 
    Data[2] = 0; 

    Data[3] = 0; 
    Data[4] = 0; 


    Data[5] = -0.5f; 
    Data[6] = 0.5f; 
    Data[7] = 0;

    Data[8] = 0; 
    Data[9] = 1; 


    Data[10] = 0.5f; 
    Data[11] = -0.5f; 
	Data[12] = 0; 

    Data[13] = 1; 
    Data[14] = 0; 
    

    Data[15] = -0.5f; 
    Data[16] = 0.5f; 
    Data[17] = 0; 

	Data[18] = 0; 
    Data[19] = 1; 


    Data[20] = 0.5f; 
    Data[21] = 0.5f; 
	Data[22] = 0; 

    Data[23] = 1; 
    Data[24] = 1; 


    Data[25] = 0.5f; 
    Data[26] = -0.5f; 
    Data[27] = 0; 

	Data[28] = 1; 
    Data[29] = 0; 

	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*30,Data,GL_DYNAMIC_DRAW);

	free(Data);
	checkGlError("Quad Buffer end");

}

void Quad::setPosition(int X,int Y, int Z)
{
	setPosition(glm::vec3(X,Y,Z));
}

void Quad::setPosition(glm::vec3 pos)
{

	m_pos		= pos;
	Translate	= glm::translate(m_pos);

}

void Quad::move(int X, int Y)
{
	m_pos.x += X;
	m_pos.y += Y;

	setPosition(m_pos);

}

void Quad::resize(int W,int H, int D)
{

	w = W;
	h = H;
	d = D;

	Scaling		= glm::scale(w,h,d);

}

void Quad::rotate(float r, int x, int y ,int z)
{

	glm::vec3	RotationAxis(x,y,z);
	Rotate   =	glm::rotate(r,RotationAxis);

}

void Quad::rotate(float r, glm::vec3 v)
{

	Rotate  =	glm::rotate(r,v);

}

void Quad::Draw(float z)
{
	checkGlError("Draw alkoi");
	glBindBuffer(GL_ARRAY_BUFFER,VBO); 

	//Enable shitz because GL
	glEnableVertexAttribArray(shader->Position);
	glEnableVertexAttribArray(shader->Uv);
	glUseProgram(shader->Program);

	glDepthFunc	(GL_LEQUAL);
	glEnable	(GL_DEPTH_TEST);

	glEnable	(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture	(GL_TEXTURE0);
	glBindTexture	(GL_TEXTURE_2D, texid);

	glUniform1i(shader->loc, 0);
	checkGlError("Uniform1i");

	//attributepointers for shader
    glVertexAttribPointer(shader->Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
	glVertexAttribPointer(shader->Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 

	//this z trying to be depth for sprite
	m_pos.z = z;

	//Translate = glm::translate(m_pos);
	
	// Create modelmatrix
	glm::mat4 model = Translate * Rotate * Scaling;

	//set 2Dcamera
	camera->Camera2D();

	//set view
	view = camera->View;

	//Projection matrix               width        heigth
	glm::mat4 proj =  glm::ortho(0.0f,1280.0f,0.0f,720.0f);

	//Model view projection
	glm::mat4 modelViewProjection = proj * model;

	//Send modelview projection to shader
	shader->setUniformMatrix("modelViewProj", modelViewProjection);
	checkGlError("modelViewProj");

	//these are vital for Draw functionality
	
    glDrawArrays(GL_TRIANGLES,0,6);

	//and final shader things: attribarrays to shader
	glDisableVertexAttribArray(shader->Position);
	glDisableVertexAttribArray(shader->Uv);
	
}


void Quad::setTexture(GLuint Texture)
{
	texid = Texture;
}

void Quad::setShader(Shader* shader2)
{
	shader = shader2;
	_color   = glm::vec4(1.0f,1.0f,1.0f,1.0f);
	_opacity = 1.0f;
	setColor(_color);
	setOpacity(_opacity);
}

void Quad::setColor(glm::vec4 color )
{
	_color = color;
	shader->setUniformVec4("color", _color);
	checkGlError("setUniformVec4");
}

void Quad::setOpacity(float opacity)
{
	_opacity = opacity;
	shader->setUniformFloat("opacity", _opacity);
	checkGlError("setUniformFloat");
}

float Quad::getX()
{
	return m_pos.x;
}

float Quad::getY()
{
	return m_pos.y;
}

float Quad::getOpacity()
{
	return _opacity;
}

Quad::~Quad(void)
{
	delete camera;
}

