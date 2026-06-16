#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


class object
{
public:
	glm::vec3 acceleration = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 velocity = glm::vec3(0.0f); 

	void collision(float deltatime, float wall,glm::vec3 position, glm::vec3 rotation);
};
