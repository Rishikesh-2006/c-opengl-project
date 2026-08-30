#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <utility>
#include <iostream>
#include "Shader.h"
#include <stb/stb_image.h>
#include <vector>
//std::pair <unsigned int, unsigned int>

static float vertex[] = {
	//Position				 Color					   UVs              Normals		
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,		0.0f,0.0f,-1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		0.0f,0.0f,-1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,		0.0f,0.0f,-1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,		0.0f,0.0f,-1.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		0.0f,0.0f,-1.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,		0.0f,0.0f,-1.0f,

	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,		0.0f,0.0f,1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		0.0f,0.0f,1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,		0.0f,0.0f,1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,		0.0f,0.0f,1.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		0.0f,0.0f,1.0f,
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,		0.0f,0.0f,1.0f,

	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		-1.0f,0.0f,0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,		-1.0f,0.0f,0.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		-1.0f,0.0f,0.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		-1.0f,0.0f,0.0f,
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,		-1.0f,0.0f,0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		-1.0f,0.0f,0.0f,

	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		1.0f,0.0f,0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,		1.0f,0.0f,0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		1.0f,0.0f,0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		1.0f,0.0f,0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,		1.0f,0.0f,0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		1.0f,0.0f,0.0f,

	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		0.0f,-1.0f,0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,		0.0f,-1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		0.0f,-1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		0.0f,-1.0f,0.0f,
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,		0.0f,-1.0f,0.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		0.0f,-1.0f,0.0f,

	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		0.0f,1.0f,0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,		0.0f,1.0f,0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		0.0f,1.0f,0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,		0.0f,1.0f,0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,		0.0f,1.0f,0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,		0.0f,1.0f,0.0f
};

static unsigned int index[] = {
	0,2,1,
	3,5,4,
	8,6,7,
	11,9,10,
	12,13,14,
	15,16,17,
	18,20,19,
	21,23,22,
	24,25,26,
	27,28,29,
	30,32,31,
	33,35,34
};




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



	//vertex information

	int index_size = sizeof(index);
	int vertex_size = sizeof(vertex);

	//member functions
	object(const char* vertex, const char* fragment) : Shader(vertex, fragment) {};

	void set_object(unsigned int& VBO, bool islightsrc);

	void set_VBO_object(unsigned int& VBO);

	void set_in_loop(std::string textureloc, int num, glm::vec3 lightpos, glm::vec3 camerapos);

	void light_in_loop(glm::vec3 lightobjectcolor, glm::mat4 view, glm::mat4 projection, glm::vec3 lightpos);

	void collision(obj_info& obj_A, obj_info& obj_B, float scale, float deltatime);

	float distance_calc(glm::vec3 posa, glm::vec3 posb);

	glm::vec3 velocity_after_collision(obj_info obj1, obj_info obj2, float scale);

	void multicollision(std::vector <obj_info>& informations, glm::vec3 camerapos, float deltatime);

	void set_shadowFBO(unsigned int& depthmapFBO, unsigned int& depthmap, int depthwidth, int depthheight);

	void set_light_in_loop(glm::vec3 lightpos, unsigned int lightVAO, glm::mat4 view, glm::mat4 projection);

	void set_lightscale(float val);

	void set_lightmultiplier(float val);

	void set_lightcolor(float val);

private:
	//light object 
	float lightscale = 1.0f;
	float multiplier = 7.0f;
	glm::vec3 lightobjectcolor = glm::vec3(1.0f, 1.0f, 1.0f);

	//vertex data
	float* vertices = vertex;
	unsigned int* indices = index;

	
};
