#include "objLoader.h"
#include <stdio.h>
#include <vector>
#include <stdlib.h>

objLoader::objLoader(void)
{
}

void objLoader::loadObj(const char* path,float** Data,int* Faces)
{
	FILE* file = fopen(path,"r");

	char line[100];
	char indicator1;
	char indicator2;
	
	std::vector<float*> Vertices = std::vector<float*>();
	std::vector<float*> Normals = std::vector<float*>();
	std::vector<float*> TextureCoordinates = std::vector<float*>();
	std::vector<int*> Indices = std::vector<int*>();
	Faces = (int*)malloc(sizeof(int));
	Faces[0] = 0;



	while(fgets(line,100,file))
	{
		
		sscanf(line,"%c%c",&indicator1,&indicator2);
		float x,y,z;

		//Verts
		if(indicator1 == 'v' && indicator2==' ')
		{
			{
				Vertices.push_back((float*)malloc(3*sizeof(float)));
				
				sscanf(line,"%*s %f %f %f",&x,&y,&z);
				
				Vertices[Vertices.size()-1][0]=x;
				Vertices[Vertices.size()-1][1]=y;
				Vertices[Vertices.size()-1][2]=z;
			}
		}
		//Normals
		else if(indicator1 == 'v' && indicator2=='n')
		{
				Normals.push_back((float*)malloc(3*sizeof(float)));
				
				sscanf(line,"%*s %f %f %f",&x,&y,&z);
				
				Normals[Normals.size()-1][0]=x;
				Normals[Normals.size()-1][1]=y;
				Normals[Normals.size()-1][2]=z;
		}

		else if(indicator1 == 'v' && indicator2=='t')
		{
				TextureCoordinates.push_back((float*)malloc(2*sizeof(float)));

				sscanf(line,"%*s %f %f",&x,&y);

				TextureCoordinates[TextureCoordinates.size()-1][0]=x;
				TextureCoordinates[TextureCoordinates.size()-1][1]=y;
		}

		else if(indicator1 == 'f' && indicator2==' ')
		{
				Indices.push_back((int*)malloc(9*sizeof(int)));
				int v1,v2,v3,uv1,uv2,uv3,vn1,vn2,vn3;
				sscanf(line,"%*s %d %*c %d %*c %d %d %*c %d %*c %d %d %*c %d %*c %d",&v1,&uv1,&vn1,&v2,&uv2,&vn2,&v3,&uv3,&vn3);

				Indices[Indices.size()-1][0] = v1-1;
				Indices[Indices.size()-1][1] = uv1-1;
				Indices[Indices.size()-1][2] = vn1-1;
				Indices[Indices.size()-1][3] = v2-1;
				Indices[Indices.size()-1][4] = uv2-1;
				Indices[Indices.size()-1][5] = vn2-1;
				Indices[Indices.size()-1][6] = v3-1;
				Indices[Indices.size()-1][7] = uv3-1;
				Indices[Indices.size()-1][8] = vn3-1;

				Faces[0]++;
		}
	}
	Data = (float**)malloc(sizeof(float*)*Indices.size());
	for(int i = 0;i<Indices.size();i++)
	{
		Data[i] = (float*)malloc(24*sizeof(float));
		for(int j = 0;j<3;j++)
		{
			Data[i][j*8+0] = Vertices[Indices[i][j*3]][0];
			Data[i][j*8+1] = Vertices[Indices[i][j*3]][1];
			Data[i][j*8+2] = Vertices[Indices[i][j*3]][2];
			
			Data[i][j*8+3] = TextureCoordinates[Indices[i][j*3+1]][0];
			Data[i][j*8+4] = TextureCoordinates[Indices[i][j*3+1]][1];
			
			Data[i][j*8+5] = Normals[Indices[i][j*3+2]][0];
			Data[i][j*8+6] = Normals[Indices[i][j*3+2]][1];
			Data[i][j*8+7] = Normals[Indices[i][j*3+2]][2];
		}
	}

	//Cleanup
	for(int i = 0; i<Vertices.size();i++)
	{
		free(Vertices[i]);
	}
	Vertices.erase(Vertices.begin(),Vertices.end());

	for(int i = 0; i<Normals.size();i++)
	{
		free(Normals[i]);
	}
	Normals.erase(Normals.begin(),Normals.end());

	for(int i = 0; i<TextureCoordinates.size();i++)
	{
		free(TextureCoordinates[i]);
	}
	TextureCoordinates.erase(TextureCoordinates.begin(),TextureCoordinates.end());

	for(int i = 0; i<Indices.size();i++)
	{
		free(Indices[i]);
	}
	Indices.erase(Indices.begin(),Indices.end());
}

objLoader::~objLoader(void)
{
}
