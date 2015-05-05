#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H
#include <string>
#include <GL/glew.h>
#include <iostream>
#include"Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const char* fileNameVs, const char* fileNameFs);
	void Bind();
	void Update(const Transform& transform, const Camera& camera);
	
	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	//static const unsigned int NUM_UNIFORMS = 1;
	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}
	const char* LoadShader(const char* fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint CreateShader(const std::string& text, unsigned int type);
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};
#endif