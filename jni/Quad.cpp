#include <Quad.h>

#include <cmath>
#include <stdlib.h>
float* Quad::Projection = NULL;

Quad::Quad(int H,int W,int D, int X,int Y,int Z)
{
	checkGlError("Quad tehty");
	w=W;
	h=H;
/*	x=X;
	y=Y;*/
	d=D;
//	z=Z;
	//setPosition(X,Y,Z);
	Translation = (float*)calloc(16,sizeof(float));
	Rotation = (float*)calloc(16,sizeof(float));
	Scale = (float*)calloc(16,sizeof(float));
	glGenBuffers(1,&VBO);
	GenBuffer();
	setPosition(X,Y,Z);
	resize(w,h,d);
	Rotate = glm::mat4(1.0f);

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
	//objLoader.loadObj("assets/cube.obj",_data,_faces);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*30,Data,GL_DYNAMIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(_faces) * sizeof(glm::vec3), &_data[0], GL_STATIC_DRAW);

	free(Data);
	checkGlError("Quad Buffer end");
}

void Quad::setPosition(int X,int Y, int Z)
{
	m_pos = glm::vec3(X,Y,Z);
	//Translation[0] = 1;
	//Translation[3] = X;
	//Translation[5] = 1;
	//Translation[7] = Y;
	//Translation[10] = 1;
	//Translation[15] = 1;
	//glm::vec3 trans(X,Y,Z);
	Translate = glm::translate(m_pos);

	//x = X; y = Y; z = Z;

}

void Quad::resize(int W,int H, int D)
{

	w = W;
	h = H;
	d = D;

	//Scale[0] = w;
	//Scale[5] = h;
	//Scale[10] = 1;
	//Scale[15] = 1;

	Scaling = glm::scale(w,h,d);
}

void Quad::rotate(float r, int x, int y ,int z)
{
	glm::vec3 RotationAxis(x,y,z);
	Rotate = glm::rotate(r,RotationAxis);
}

void Quad::rotate(float r, glm::vec3 v)
{
	Rotate = glm::rotate(r,v);
}

void Quad::Draw(float z)
{
	checkGlError("Draw alkoi");
	glEnableVertexAttribArray(shader->Position);
	glEnableVertexAttribArray(shader->Uv);
	glUseProgram(shader->Program);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texid);

	glUniform1i(shader->loc, 0);
	checkGlError("Uniform1i");


    glVertexAttribPointer(shader->Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
	glVertexAttribPointer(shader->Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 
	//glUniformMatrix4fv(shader->loc2,1,GL_FALSE,Projection);
	//glUniformMatrix4fv(shader->loc3,1,GL_FALSE,Translation);
	//glUniformMatrix4fv(shader->loc4,1,GL_FALSE,Rotation);
	//glUniformMatrix4fv(shader->loc5,1,GL_FALSE,Scale);
	//shader->setUniformMatrix("Rotation", Rotate);
	//checkGlError("Rotation");
	//shader->setUniformMatrix("Scale", Scaling);
	//checkGlError("Rotation");
	m_pos.z = z;
	//Translate = glm::translate(m_pos);
	
	glm::mat4 model = Translate * Rotate * Scaling;
		//glm::rotate( angle*100.0f, 0.0f,1.0f,1.0f );

	glm::mat4 view = glm::lookAt(
		glm::vec3(0,0,1), // Camera is at (4,3,3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	
	//Sets perspective camera.           ANGLE, WIDTH   HEIGHT  NEAR   FAR
	//glm::mat4 proj = glm::perspectiveFov(45.0f,1280.0f, 720.0f, 0.001f,100.0f);
	glm::mat4 proj =  glm::ortho(0.0f,1280.0f,0.0f,720.0f);
	glm::mat4 modelViewProjection = proj * model;

	shader->setUniformMatrix("modelViewProj", modelViewProjection);
	checkGlError("modelViewProj");
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
