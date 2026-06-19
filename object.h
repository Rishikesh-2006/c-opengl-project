#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <array>

class object : public Shader
{

public:
	unsigned int CUBEVAO;
	unsigned int CUBEEBO;
	unsigned int CUBEVBO;
	glm::vec3 acceleration = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 velocity = glm::vec3(0.0f); 
	object(const char* vertex, const char* fragment) : Shader(vertex, fragment) {};

	void Set_Object(float* vertices, int num_items, int stride, unsigned int* indices,const std::array<int, 2>& tex = { 0 , 0 });

	void Set_Object_AVBO(float* vertices, int num_items, unsigned int* indices, int stride, unsigned int VBO, const std::array <int, 2>& tex = { 0,0 });

};
