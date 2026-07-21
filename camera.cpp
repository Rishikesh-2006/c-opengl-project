#include "camera.h"


void camera::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	camera* cam = static_cast<camera*>(glfwGetWindowUserPointer(window));

	if(!cam)
	{
		return;
	}

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (cam->firstmouse)
	{
		cam->lastx = xpos;
		cam->lasty = ypos;
		cam->firstmouse = false;
	}

	float xoffset = xpos - cam->lastx;
	float yoffset = cam->lasty - ypos; // reversed since y-coordinates go from bottom to top
	cam->lastx = xpos;
	cam->lasty = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cam->yaw += xoffset;
	cam->pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (cam->pitch > 89.0f)
		cam->pitch = 89.0f;
	if (cam->pitch < -89.0f)
		cam->pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
	front.y = sin(glm::radians(cam->pitch));
	front.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
	cam->camerafront = glm::normalize(front);
}


void camera::processInput(GLFWwindow* window, float speed , float deltatime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	const float cameraSpeed = speed * deltatime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camerapos += cameraSpeed * camerafront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camerapos -= cameraSpeed * camerafront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camerapos -= glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camerapos += glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camerapos.y += 2.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		player_factor = 0.5f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
		player_factor = 1.8f;



}

void camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera* cam = static_cast<camera*>(glfwGetWindowUserPointer(window));

	if (!cam)
	{
		return;
	}

	cam->fov -= (float)yoffset;

	if (cam->fov < 1.0f)
	{
		cam->fov = 1.0f;
	}
	if (cam->fov > 45.0f)
	{
		cam->fov = 45.0f;
	}
}

void camera::displaycamcoors(bool position, bool front)
{
	if (position = true)
	{
		std::cout <<"{" << camerapos.x << "," << camerapos.y << "," << camerapos.z <<"}" << std::endl;
	}

	if (front = true)
	{
		std::cout << "{" <<  camerafront.x << "," << camerafront.y << "," << camerafront.z << "}" << std::endl;
	}
}

glm::mat4 camera::set_view()
{
	return glm::lookAt(camerapos, camerapos + camerafront, cameraup);
}

glm::mat4 camera::set_projection()
{
	return glm::perspective(glm::radians(fov), float(scwidth) / float(scheight), 0.1f, 400.0f);
}

void camera::set_caminputs(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}