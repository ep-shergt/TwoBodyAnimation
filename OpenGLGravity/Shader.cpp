#include "shader.h"
#include <fstream>
Shader::Shader(const char* fileNameVs, const char* fileNameFs)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileNameVs), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileNameFs), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	//glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 1, "normal");
	
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

	/*m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
	m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
	m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");*/
}
Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}
void Shader::Bind()
{
	glUseProgram(m_program);
}


void Shader::Update(const Transform& transform, const Camera& camera)
{
	//glm::mat4 MVP = transform.GetMVP(camera);
	glm::mat4 model = camera.GetViewProjection()*transform.GetModel();
	//glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	//glUniform3f(m_uniforms[2], 0.0f, 0.0f, 1.0f);
}
const char* Shader::LoadShader(const char* fileName)
{
	// Open the file
	FILE* fp = fopen(fileName, "r");
	// Move the file pointer to the end of the file and determing the length
	fseek(fp, 0, SEEK_END);
	long file_length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* contents = new char[file_length + 1];
	// zero out memory
	for (int i = 0; i < file_length + 1; i++) {
		contents[i] = 0;
	}
	// Here's the actual read
	fread(contents, 1, file_length, fp);
	// This is how you denote the end of a string in C
	contents[file_length + 1] = '\0';
	fclose(fp);

	/*std::cout << "================================" << std::endl;
	std::cout << contents << std::endl;
	std::cout << "================================" << std::endl;*/

	return contents;

}
void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);
	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);
	if (shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;
	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();
	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");
	return shader;
}