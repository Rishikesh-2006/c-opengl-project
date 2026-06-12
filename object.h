#pragma once

//temporary may remove or combine with a future class

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


class object
{


public:
	void rotateobject(unsigned int shaderprogram, float x, float y, float z);

	glm::mat4 multiple3d(unsigned int shaderprogram, int width, int height, float fov);

	void camera(unsigned int shaderprogram, glm::vec3 camerapos, glm::vec3 cameraup, glm::vec3 camerafront);

};
