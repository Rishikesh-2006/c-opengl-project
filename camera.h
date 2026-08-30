#pragma once
#include <GLFW/glfw3.h>
#include "Shader.h"

class camera
{
	
public:
	int scheight = 1080;
	int scwidth = 1920;

	//camera
	bool firstmouse = true;
	float yaw = 0.0f;
	float pitch = 0.0f;
	float lastx = scwidth / 2.0f;
	float lasty = scheight / 2.0f;
	float fov = 45.0f;


	float player_factor = 0.5;
	float speed = 40.0f;

	glm::vec3 camerapos = { -52.0f,7.0f,-17.0f };
	glm::vec3 camerafront = { 0.99f, -0.07f, 0.008f };
	glm::vec3 cameraup = { 0.0f, 1.0f ,0.0f };


    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

	void processInput(GLFWwindow* window, float speed,float deltatime);

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void displaycamcoors(bool position, bool front);

	glm::mat4 set_view();

	glm::mat4 set_projection();

	void set_caminputs(GLFWwindow* window);

	void invert_pitch();
};

