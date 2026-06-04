#include <stb/stb_image.h>
#include <iostream>
#include "Shader.h"
#include "object.h"

int scheight = 800;
int scwidth = 900;


glm::vec3 camerapos = { 0.0f, 0.0f ,0.0f };
glm::vec3 camerafront = { 0.0f, 0.0f ,-3.0f };
glm::vec3 cameraup = { 0.0f, 1.0f ,0.0f };


float deltatime = 0.0f;
float lastframe = 0.0f;
float currentframe;




void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeedvertical = 3.5*deltatime;
	float cameraSpeedhorizontal = 5 * deltatime;
	if (glfwGetKey(window, GLFW_KEY_W) || (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
		camerapos += cameraSpeedvertical * camerafront;
	if (glfwGetKey(window, GLFW_KEY_S) || (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
		camerapos -= cameraSpeedvertical * camerafront;
	if (glfwGetKey(window, GLFW_KEY_A) || (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS))
		camerapos -= glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeedhorizontal;
	if (glfwGetKey(window, GLFW_KEY_D) || (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS))
		camerapos += glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeedhorizontal;
}

bool firstmouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastx = scwidth / 2;
float lasty = scheight / 2;
float zoom = 45.0f;

void mouse_callback(GLFWwindow* window, double xposin, double yposin)
{
	float xpos = static_cast<float>(xposin);
	float ypos = static_cast<float>(yposin);

	if (firstmouse)
	{
		lastx = xpos;
		lasty = ypos;
		firstmouse = false;
	}

	float xoffset = xpos - lastx;
	float yoffset = lasty - ypos;
	lastx = xpos;
	lasty = ypos;


	float sensetivity = 0.1;
	xoffset *= sensetivity;
	yoffset *= sensetivity;



	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	camerafront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	zoom -= (float)yoffset;

	if (zoom < 1.0f)
	{
		zoom = 1.0f;
	}

	if (zoom > 45.0f)
	{
		zoom = 45.0f;
	}
}


int main()
{


	/*float vertices[] = {
		0.25f,0.25f,0.0f,	1.0f, 0.0f, 0.0f,	1.0f,1.0f,
		0.25f,-0.25f,0.0f,	0.0f, 1.0f, 0.0f,	1.0f,0.0f,
		-0.25f,-0.25f,0.0f,	0.0f, 0.0f, 1.0f,	0.0f,0.0f,
		-0.25f,0.25f,0.0f,	1.0f,0.0f,1.0f,		0.0f,1.0f
	};*/


	float vertices[] = {
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,		  0.0f, 1.0f
	};

	/*unsigned int indices[] = {
		0,1,3,
		1,2,3
	};*/

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(scheight,scwidth, "opengl", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "failed to open window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
	
	glViewport(0, 0, scheight, scwidth);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//shader class to initialize and combine vertex and fragement shader
	Shader shader;

	shader.activateshader("default.vert", "default.frag");
	

	//this ensures the faces on the front are shown and the back ones are hidden
	glEnable(GL_DEPTH_TEST);

	//vertex buffers , arrays

	GLuint VAO, VBO;
	//GLuint EBO;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 8 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, 0, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, 0, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//textures

	stbi_set_flip_vertically_on_load(true);
	unsigned int textures;

	glGenTextures(1, &textures);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrchannels;

	unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrchannels, 0);
	

	if (data)
	{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	}

	else
	{
		std::cout << "failed to get data";
	}
	
	stbi_image_free(data);
	object render1;

	unsigned int shaderid = shader.shprgm();

	while (!glfwWindowShouldClose(window))
	{
		currentframe = glfwGetTime();
		deltatime = currentframe - lastframe;
		lastframe = currentframe;

		processInput(window);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, textures);

		shader.useshader();
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(VAO);

		render1.camera(shaderid, camerapos, cameraup, camerafront);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		render1.make3d(scwidth, scheight,45.0f);
		render1.mattoshader(shaderid);
		//render1.rotateobject(shaderid, 0.4f, 0.5f, 0.7f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader.deleteshader();
	glDeleteTextures(1, &textures);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}