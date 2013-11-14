#include "Texture.h"
#include <FileReader.h>

Texture::Texture(void)
{

}


Texture::~Texture(void)
{
	
}

void Texture::loadTexture(const char* textureName)
{
	GLubyte* pixels;
	FileReader *FR = new FileReader(textureName);

	unsigned char*buffer = (unsigned char*)malloc(sizeof(unsigned char)*4);
	//move to position 12, next 4 bytes are size
	FR->FileSeek(12,0);
	FR->ReadBytes(4,buffer);
	int sizex= buffer[0]+buffer[1]*256;
	int sizey= buffer[2]+buffer[3]*256;
	free(buffer);

	buffer = (unsigned char*)malloc(sizeof(unsigned char)*1);
	FR->FileSeek(16,0);
	FR->ReadBytes(1,buffer);
	int bpp = buffer[0];
	free(buffer);

	int datasize = sizex*sizey*bpp/8;
	pixels = (unsigned char*)malloc(sizeof(unsigned char)*datasize);
	unsigned char *Buffer = (unsigned char*)malloc(sizeof(unsigned char)*datasize);

	FR->FileSeek(18,0);
	FR->ReadBytes(datasize,Buffer);
	for(int i = 0; i<datasize;i+=4)
	{
		pixels[i+0] = Buffer[i+2];
		pixels[i+1] = Buffer[i+1];
		pixels[i+2] = Buffer[i+0];
		pixels[i+3] = Buffer[i+3];
	}
	delete FR;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,&texture);
	glActiveTexture(GL_TEXTURE0);

	//Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture);

	// Load the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizex, sizey, 0, GL_RGBA,
					GL_UNSIGNED_BYTE, pixels);


	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
}