#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include<string>
#include<GL\glew.h>




class Texture
{
public:
	Texture(const char* fileName);

	void Bind(unsigned int unit);

	virtual ~Texture();


private: 

	
	Texture(const Texture& other){}
	void operator=(const Texture& other){}

	GLuint m_texture;

};

#endif // !TEXTURE.H