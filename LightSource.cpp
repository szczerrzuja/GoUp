#include "LightSource.h"

glm::mat4x4 viewMatrix = glm::mat4(1.0f);
glm::mat4x4 ProjectionMatrix = glm::mat4(1.0f);
glm::vec3 CameraPosition = glm::vec3(1.0f);
glm::vec3 CameraDir = glm::vec3(1.0f);
LightSource::LightSource(std::vector<Shader*>* shad,int type, glm::vec3 pos, glm::vec4 col , glm::vec3 amb , glm::vec3 diff , glm::vec3 spec )
{
	position = pos;
	color = col;

	ambient = amb;
	diffuse = diff;
	specular = spec;
	shaders = shad;
	switch (type)
	{
	case 0:
		type = 0;
		break;
	case 1:
		type = 1;
		break;
	case 2:
		type = 2;
		break;
	default:
		type = 0;
		break;
	}
	initLightSource();
}

LightSource::~LightSource()
{
	glDeleteVertexArrays(1, &VAO);
}
void LightSource::lightThemAll( GLuint OBJVAO)
{
	
}
void LightSource::initLightSource()
{
	//tutaj podobnie jak w meshu- mo¿na zrobiæ œwiec¹cy obiekt
	

}
