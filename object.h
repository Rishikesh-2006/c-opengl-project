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

struct obj_info
{
	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 position;
	float mass;

};

class object : public Shader
{
public:
	unsigned int VAO = 2;  //correct value is 2
	unsigned int EBO = 0;

	float lightscale = 1.0f;
	float multiplier = 10.0f;



	object(const char* vertex, const char* fragment) : Shader(vertex, fragment) {};

	void set_object(unsigned int& VBO, unsigned int* indices, int indices_size, bool islightsrc);

	void set_VBO_object(unsigned int& VBO, float* vertices, int vertice_size, unsigned int* indices, int indice_size);

	void set_in_loop(std::string textureloc, int num, glm::vec3 lightobjectcolor, glm::vec3 lightpos, glm::vec3 camerapos);

	void light_in_loop(glm::vec3 lightobjectcolor, glm::mat4 view, glm::mat4 projection, glm::vec3 lightpos);

	void collision(obj_info& obj_A, obj_info& obj_B, float scale, float deltatime);

	float distance_calc(glm::vec3 posa, glm::vec3 posb);

	glm::vec3 velocity_after_collision(obj_info obj1, obj_info obj2, float scale);

	void multicollision(std::vector <obj_info>& informations, glm::vec3 camerapos, float deltatime);

	void set_shadowFBO(unsigned int& depthmapFBO, unsigned int& depthmap, int depthwidth, int depthheight);
};
