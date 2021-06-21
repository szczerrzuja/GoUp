#pragma once

#include "Shaders/Shader.h"
#include "Vertex.h"
#include <vector>
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#ifndef LightSource_H
#define LightSource_H
extern glm::mat4 viewMatrix, ProjectionMatrix;
extern glm::vec3 CameraPosition, CameraDir ;
class LightSource
{
private:
	GLuint VBO, VAO;

	glm::vec3 position;
	glm::vec4 color;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	std::vector<Shader*> *shaders;
	int type;
	void initLightSource();
public:
	//type = 0 - directional, type= 1 - PointLight, type = 2 - spotlight
	LightSource(std::vector<Shader*>* shad,int type, glm::vec3 pos = {0,0,0}, glm::vec4 col = { 1.0, 1.0, 1.0, 1.0 },
		glm::vec3 amb = { 0.2, 0.2, 0.2 }, glm::vec3 diff ={ 0.8, 0.8, 0.8 }, glm::vec3 spec = { 1.0, 1.0, 1.0 });
	~LightSource();
	void lightThemAll( GLuint VAO);
	
};
#endif