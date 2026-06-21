#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <utility>
#include <iostream>
//std::pair <unsigned int, unsigned int>

class object
{
public:
	unsigned int floorVAO;
	unsigned int floorEBO;

	void set_object(unsigned int &VBO, unsigned int* indices,int indice_size);
};
