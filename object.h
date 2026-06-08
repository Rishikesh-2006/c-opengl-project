#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


class object
{


public:
	void make3d(unsigned int shaderprogram, int width, int height, float fov);

	void rotateobject(unsigned int shaderprogram,float x, float y , float z);

	void multiple3d(unsigned int shaderprogram, int width, int height, float fov);

	glm::mat4 camera(unsigned int shaderprogram,glm::vec3 camerapos, glm::vec3 cameraup, glm::vec3 camerafront);

	void setview(unsigned int shaderprogram, glm::mat4 view);
};

