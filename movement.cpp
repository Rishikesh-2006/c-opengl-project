#include "movement.h"

void movement::utility(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void movement::playermovement(GLFWwindow* window,glm::vec3 camerapos, glm::vec3 camerafront, glm::vec3 cameraup)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camerapos += cameraspd * camerafront;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camerapos -= cameraspd * camerafront;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camerapos += cameraspd * glm::normalize(glm::cross(camerafront,cameraup));
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camerapos -= cameraspd * glm::normalize(glm::cross(camerafront, cameraup));
	}
}