#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
class object
{
	glm::mat4 mainmodel;
	glm::mat4 mainview;
	glm::mat4 mainprojection;
public:
	void rotateobject(unsigned int shaderprogram,float x, float y , float z);

	void make3d(int width,int height,float fov);

	void mattoshader(unsigned int shaderprogram);

	void camera(unsigned int shaderprogram,glm::vec3 camerapos, glm::vec3 cameraup, glm::vec3 camerafront);

};

