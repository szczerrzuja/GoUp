#include "initProgVal.h"
void initProgVal::setViewMarix(Shader& shader)
{
	
	GLint viewLoc = glGetUniformLocation(shader.Program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	GLint CamDir = glGetUniformLocation(shader.Program, "light.direction");
	glUniform3f(CamDir, CameraDir.x, CameraDir.y, CameraDir.z);

}
void initProgVal::setProjetionMatrix(Shader& shader)
{
	
	glGetFloatv(GL_PROJECTION_MATRIX, glm::value_ptr(ProjectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

}
void initProgVal::setCameraPos( Shader& shader)
{
	GLint viewPosLoc = glGetUniformLocation(shader.Program, "viewPos");
	glUniform3f(viewPosLoc, CameraPosition.x, CameraPosition.y, CameraPosition.z);
	viewPosLoc = glGetUniformLocation(shader.Program, "light.position");
	glUniform3f(viewPosLoc, CameraPosition.x, CameraPosition.y, CameraPosition.z);
}
void initProgVal::test(Shader& shader)
{
	GLint lightColorLoc = glGetUniformLocation(shader.Program, "light.Color");
	//tutaj te zmienne s¹ zmieniane
	glUniform3f(lightColorLoc, 0.6f, 0.8f, 0.8f);

	glUniform1f(glGetUniformLocation(shader.Program, "light.cutOff"), glm::cos(glm::radians(12.5f)));
	glUniform1f(glGetUniformLocation(shader.Program, "light.outerCutOff"), glm::cos(glm::radians(17.5f)));
	glUniform1f(glGetUniformLocation(shader.Program, "light.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.Program, "light.linear"), 0.0045);
	glUniform1f(glGetUniformLocation(shader.Program, "light.quadratic"), 0.0008);
}