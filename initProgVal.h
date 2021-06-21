#pragma once
#include "LightSource.h"
#include "Shaders/Shader.h"
class initProgVal
{
public:

	void setViewMarix( Shader &shader);
	void setProjetionMatrix( Shader &shader);
	void setCameraPos( Shader& shader);
	void test(Shader& shader);


};

