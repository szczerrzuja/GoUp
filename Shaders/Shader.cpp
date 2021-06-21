#include "Shader.h"
Shader::Shader(std::string vertexPath, std::string fragmetnPath)
{
	//odczytanie shadera z pliku
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//upewnienie ¿e ifstream mo¿e wyrzuciæ wyj¹tek 
	//¿e coœ siê Ÿle wczyta³o
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmetnPath);
		std::stringstream  vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		exit(1);
	}
	//compile shaders
	GLuint vertex, fragment;
	GLint success;
	char Log[1024];
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(Program, 1024, NULL, Log);
		exit(1);
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Program, 512, NULL, Log);
		exit(1);
	}
	Program = glCreateProgram();
	glAttachShader(Program, vertex);
	glAttachShader(Program, fragment);
	glLinkProgram(Program);
	// Exit if linking error
	glGetProgramiv(Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(Program, 512, NULL, Log);
		exit(1);
	}
	// Delete shader becouse they are not needed anymore
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::run()
{
	glUseProgram(this->Program);
}
