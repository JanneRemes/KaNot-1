#include <Quad.h>
#include <Shader.h>
#include <cmath>
#include <stdlib.h>

float* Quad::Projection = NULL;

Quad::Quad(int H,int W,int X,int Y)
{
	w=W;
	h=H;
	x=X;
	y=Y;

	Translation = (float*)calloc(16,sizeof(float));
	Rotation = (float*)calloc(16,sizeof(float));
	Scale = (float*)calloc(16,sizeof(float));
	glGenBuffers(1,&VBO);
	GenBuffer();
	move(x,y);
	resize(w,h);
	rotate(0);

}

void Quad::GenBuffer()
{
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
}

void Quad::move(int X,int Y)
{
	Translation[0] = 1;
	Translation[3] = X;
	Translation[5] = 1;
	Translation[7] = Y;
	Translation[10] = 1;
	Translation[15] = 1;
	x = X; y = Y;
}

void Quad::resize(int W,int H)
{
	w = W;
	h = H;
	
	Scale[0] = w;
	Scale[5] = h;
	Scale[10] = 1;
	Scale[15] = 1;

}

void Quad::rotate(float r)
{
	Rotation[0] = std::cos(-r);
	Rotation[1] = -std::sin(-r);
	Rotation[4] = std::sin(-r);
	Rotation[5] = std::cos(-r);
	Rotation[10] = 1;
	Rotation[15] = 1;
}

void Quad::Draw(float z)
{
	glEnableVertexAttribArray(shader->Position);
	glEnableVertexAttribArray(shader->Uv);
	glUseProgram(shader->Program);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Translation[11] = z;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texid);

	glUniform1i(shader->loc, 0); 

    glVertexAttribPointer(shader->Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
	glVertexAttribPointer(shader->Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 
	glUniformMatrix4fv(shader->loc2,1,GL_FALSE,Projection);
	glUniformMatrix4fv(shader->loc3,1,GL_FALSE,Translation);
	glUniformMatrix4fv(shader->loc4,1,GL_FALSE,Rotation);
	glUniformMatrix4fv(shader->loc5,1,GL_FALSE,Scale);
	glBindBuffer(GL_ARRAY_BUFFER,VBO); 
    glDrawArrays(GL_TRIANGLES,0,6);
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
}

Quad::~Quad(void)
{

}
