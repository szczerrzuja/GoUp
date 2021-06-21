#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
class Shader
{
public:
	GLuint Program;
	Shader(std::string vertexPath, std::string fragmetnPath);
	void run();


};