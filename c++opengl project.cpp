#include <stb/stb_image.h>
#include <iostream>
#include "Shader.h"
#include "object.h"

void checkKey(GLFWwindow* window);

int main()
{
int scheight = 800;
int scwidth = 800;

	/* Triangle
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top 

	};*/

	float vertices[] = {
		0.5f,0.5f,0.0f,		1.0f, 0.0f, 0.0f,   1.0f,1.0f,
		0.5f,-0.5f,0.0f,	0.0f, 1.0f, 0.0f,	1.0f,0.0f,
		-0.5f,-0.5f,0.0f,	0.0f, 0.0f, 1.0f,	0.0f,0.0f,
		-0.5f,0.5f,0.0f,	1.0f,0.0f,1.0f,		0.0f,1.0f
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

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

	//shader class to initialize and combine vertex and fragement shader
	Shader shader;

	shader.activateshader("default.vert", "default.frag");
	
	
	//vertex buffers , arrays

	GLuint VAO, VBO;
	GLuint EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
		checkKey(window);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, textures);

		shader.useshader();
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		render1.rotateobject(shaderid, 0.4, 0.5, 0.7);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader.deleteshader();
	glDeleteTextures(1, &textures);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}

void checkKey(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}