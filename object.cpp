#include "object.h"

void object::rotateobject(unsigned int shaderprogram, float x, float y, float z)
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(x, y, z));

	unsigned int transformLoc = glGetUniformLocation(shaderprogram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}


void object::multiple3d(unsigned int shaderprogram,int width, int height, float fov)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	projection = glm::perspective(glm::radians(fov), float(width / height), 0.1f, 100.0f);
	int projectionloc = glGetUniformLocation(shaderprogram, "projection");
	glUniformMatrix4fv(projectionloc, 1, GL_FALSE, glm::value_ptr(projection));

	for (int i = 0;i <10;i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		int modelloc = glGetUniformLocation(shaderprogram, "model");
		glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}


void object::camera(unsigned int shaderprogram,glm::vec3 camerapos, glm::vec3 cameraup, glm::vec3 camerafront)
{
	glm::mat4 view = glm::lookAt(camerapos, camerapos + camerafront, cameraup);
	int viewloc = glGetUniformLocation(shaderprogram, "view");
	glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));
}