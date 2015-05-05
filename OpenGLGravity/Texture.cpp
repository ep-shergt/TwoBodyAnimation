
#include <cassert>
#include <iostream>
#include "Texture.h"

  inline  void loadBitmapFromFile(const char* filename, int* width, int* height, int* size, unsigned char** pixel_data) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Couldn't open file... aborting\n");
	}
	short identifier = -1;
	fread(&identifier, 1, sizeof(short), fp); printf("Identifer is: %c\n", identifier);
	int filesize = -1;
	fread(&filesize, 1, sizeof(int), fp); printf("filesize is: %d\n", filesize);
	int reserved = -1;
	fread(&reserved, 1, sizeof(int), fp); printf("reserved is: %d\n", reserved);
	int bitmap_offset = -1;
	fread(&bitmap_offset, 1, sizeof(int), fp); printf("bitmap_offset is: %d\n", bitmap_offset);
	int bitmap_header_size = -1;
	fread(&bitmap_header_size, 1, sizeof(int), fp); printf("bitmap_header_size is: %d\n", bitmap_header_size);
	int bitmap_width = -1;
	fread(&bitmap_width, 1, sizeof(int), fp); printf("bitmap_width is: %d\n", bitmap_width);
	int bitmap_height = -1;
	fread(&bitmap_height, 1, sizeof(int), fp); printf("bitmap_height is: %d\n", bitmap_height);
	short bitmap_planes = -1;
	fread(&bitmap_planes, 1, sizeof(short), fp); printf("bitmap_planes is: %d\n", bitmap_planes);
	short bits_per_pixel = -1;
	fread(&bits_per_pixel, 1, sizeof(short), fp); printf("bits_per_pixel is: %d\n", bits_per_pixel);
	int compression = -1;
	fread(&compression, 1, sizeof(int), fp); printf("compression is: %d\n", compression);
	int bitmap_data_size = -1;
	fread(&bitmap_data_size, 1, sizeof(int), fp); printf("bitmap_data_size is: %d\n", bitmap_data_size);
	int hresolution = -1;
	fread(&hresolution, 1, sizeof(int), fp); printf("hresolution is: %d\n", hresolution);
	int vresolution = -1;
	fread(&vresolution, 1, sizeof(int), fp); printf("vresolution is: %d\n", vresolution);
	int num_colors = -1;
	fread(&num_colors, 1, sizeof(int), fp); printf("num_colors is: %d\n", num_colors);
	int num_important_colors = -1;
	fread(&num_important_colors, 1, sizeof(int), fp); printf("num_important_colors is: %d\n", num_important_colors);

	// Jump to the data already!
	fseek(fp, bitmap_offset, SEEK_SET);
	unsigned char* data = new unsigned char[bitmap_data_size];
	// Read data in BGR format
	fread(data, sizeof(unsigned char), bitmap_data_size, fp);

	// Make pixel_data point to the pixels
	*pixel_data = data;
	*size = bitmap_data_size;
	*width = bitmap_width;
	*height = bitmap_height;
	fclose(fp);
}


GLuint	 texBufferID;	// We have to create a buffer to hold the image. However, it WON'T go in the vertex buffer
GLuint	 texCoordID;	// The ID of the "texCoord" variable in the shader
GLuint	 texID;			// The ID of the "texture" variable in the shader
GLubyte* imageData;


Texture::Texture(const char* fileName)
{
	int bmpWidth = -1;
	int bmpHeight = -1;
	int bmpSize = -1;
	loadBitmapFromFile(fileName, &bmpWidth, &bmpHeight, &bmpSize, (unsigned char**)&imageData);
	if (imageData == NULL)
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpWidth, bmpHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
	
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}





void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);


}
