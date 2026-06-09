#include <stb/stb_image.h>
#include <iostream>
#include "Shader.h"
#include "object.h"


int scheight = 800;
int scwidth = 800;


glm::vec3 camerapos = { 0.0f, 0.0f ,5.0f };
glm::vec3 camerafront = { 0.0f, 0.0f ,-3.0f };
glm::vec3 cameraup = { 0.0f, 1.0f ,0.0f };



float deltatime = 0.0f;
float lastframe = 0.0f;
float currentframe;

glm::vec3 lightpos(0.0969613f, 1.86839f, -11.0884f);


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeedvertical = 3.5 * deltatime;
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



glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  0.0f,  0.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f)
};

void multicubes(unsigned int shaderprogram, int width, int height, float fov)
{

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(fov), float(width / height), 0.1f, 100.0f);
	int projectionloc = glGetUniformLocation(shaderprogram, "projection");
	glUniformMatrix4fv(projectionloc, 1, GL_FALSE, glm::value_ptr(projection));

	for (int i = 0;i < 10;i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);

		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		int modelloc = glGetUniformLocation(shaderprogram, "model");
		glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));

		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}

void singlecube(unsigned int shaderprogram, int width, int height, float fov);

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

	unsigned int indices[] = {
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,
		24,25,26,
		27,28,29,
		30,31,32,
		33,34,35
	};



	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(scheight, scwidth, "opengl", NULL, NULL);

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//shader class to initialize and combine vertex and fragement shader
	Shader shader;
	Shader light;
	shader.activateshader("default.vert", "default.frag");
	light.activateshader("lightobject.vert", "lightobject.frag");

	//this ensures the faces on the front are shown and the back ones are hidden
	glEnable(GL_DEPTH_TEST);

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

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, 0, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, 0, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//lightobject
	
	GLuint lightvao;

	glGenVertexArrays(1, &lightvao);
	glBindVertexArray(lightvao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	 
	//textures

	stbi_set_flip_vertically_on_load(true);
	unsigned int textures;

	glGenTextures(1, &textures);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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

	unsigned int shaderid = shader.getshdr();

	while (!glfwWindowShouldClose(window))
	{
		currentframe = glfwGetTime();
		deltatime = currentframe - lastframe;
		lastframe = currentframe;

		std::cout << camerafront.x << "," << camerafront.y << "," << camerafront.z << std::endl;
		
		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, textures);

		shader.useshader();

		shader.setvec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setvec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(VAO);

		//camera

		glm::mat4 view = glm::lookAt(camerapos, camerapos + camerafront, cameraup);
		shader.setmat4("view", view);

		//shader 1 cubes

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(width / height), 0.1f, 100.0f);
		shader.setmat4("projection", projection);

		for (int i = 0;i < 10;i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);

			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			shader.setmat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);


		}

		light.useshader();
		light.setmat4("view", view);
		light.setmat4("projection", projection);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightpos);
		model = glm::scale(model, glm::vec3(0.5f));
		light.setmat4("model", model);

		glBindVertexArray(lightvao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		

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

//light cube pos 0.0969613,1.86839,-11.0884
