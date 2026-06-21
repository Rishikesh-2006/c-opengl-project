#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <utility>
#include <iostream>
#include "Shader.h"
//std::pair <unsigned int, unsigned int>

class object : public Shader
{
public:
	unsigned int VAO = 2;  //controlling the wall reflection correct value is 2
	unsigned int EBO = 0;


	object(const char* vertex, const char* fragment) : Shader(vertex, fragment){};
	void set_object(unsigned int& VBO, unsigned int* indices, int indices_size, bool lightsrc);
	void set_VBO_object(unsigned int& VBO, float* vertices, int vertice_size, unsigned int* indices, int indice_size);
};
