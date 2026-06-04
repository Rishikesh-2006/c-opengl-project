#include "object.h"

void object::rotateobject(unsigned int shaderprogram, float x, float y, float z)
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(x, y, z));

	unsigned int transformLoc = glGetUniformLocation(shaderprogram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void object::make3d(int width,int height,float fov)
{
	glm::mat4 model = glm::mat4(1.0f);
	mainmodel = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	mainprojection = glm::perspective(glm::radians(fov), float(width / height), 0.1f, 100.0f);
}

void object::mattoshader(unsigned int shaderprogram)
{
	int modelloc = glGetUniformLocation(shaderprogram, "model");
	glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(mainmodel));

	int projectionloc = glGetUniformLocation(shaderprogram, "projection");
	glUniformMatrix4fv(projectionloc, 1, GL_FALSE, glm::value_ptr(mainprojection));
}
void object::camera(unsigned int shaderprogram,glm::vec3 camerapos, glm::vec3 cameraup, glm::vec3 camerafront)
{
	glm::mat4 view = glm::lookAt(camerapos, camerapos + camerafront, cameraup);
	int viewloc = glGetUniformLocation(shaderprogram, "view");
	glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));
}