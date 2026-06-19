#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Shader.h"
#include <array>

class object : public Shader
{
	using Shader::Shader;
public:

	GLuint OGVBO;

	glm::vec3 acceleration = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 velocity = glm::vec3(0.0f); 

	object(const char* vertexpath, const char* fragmentpath) : Shader(vertexpath, fragmentpath) {};

	void Set_Object(float vertices[],int num_items,int stride, const std::array<int, 2>& tex = {0 , 0}, unsigned int indices[]);

	void Set_Object_AVBO(float vertices[], int num_items, unsigned int indices[], const std::array <int, 2>& tex = { 0,0 }, int stride, unsigned int VBO);

};
