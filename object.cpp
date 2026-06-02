#include "object.h"

void object::rotateobject(unsigned int shaderprogram, float x, float y, float z)
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(x, y, z));

	unsigned int transformLoc = glGetUniformLocation(shaderprogram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}