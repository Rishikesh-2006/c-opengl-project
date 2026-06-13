#include <stb/stb_image.h>
#include <iostream>
#include "Shader.h"
#include "object.h"


int scheight = 800;
int scwidth = 800;

//camera vals
glm::vec3 camerapos = { 0.0f, 0.0f ,5.0f };
glm::vec3 camerafront = { 0.0f, 0.0f ,-3.0f };
glm::vec3 cameraup = { 0.0f, 1.0f ,0.0f };
bool firstmouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastx = scwidth / 2;
float lasty = scheight / 2;
float zoom = 45.0f;


float deltatime = 0.0f;
float lastframe = 0.0f;
float currentframe;

//lightobject
glm::vec3 lightpos(5.0f, 0.0f, 6.0f);
glm::vec3 lightobjectcolor(1.0f, 1.0f, 1.0f);
glm::vec4 background_light = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

void mouse_callback(GLFWwindow* window, double xposin, double yposin);
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


int main()
{
	float vertices[] = {
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

	unsigned int indices[] = {
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

	//loading opengl using glad
	gladLoadGL();
	glViewport(0, 0, scheight, scwidth);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//shader class to initialize and combine vertex and fragement shader
	Shader wall;
	Shader light;
	Shader floor;
	wall.activateshader("wall.vert", "wall.frag");
	light.activateshader("lightobject.vert", "lightobject.frag");
	floor.activateshader("floor.vert", "floor.frag");
	//this ensures the faces on the front are shown and the back ones are hidden

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	//vertex buffers , arrays

	GLuint CUBEVAO, CUBEVBO;
	GLuint CUBEEBO;

	glGenVertexArrays(1, &CUBEVAO);
	glGenBuffers(1, &CUBEVBO);

	glBindVertexArray(CUBEVAO);

	glBindBuffer(GL_ARRAY_BUFFER, CUBEVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &CUBEEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CUBEEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, 0, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	//lightobject

	GLuint lightvao, lightEBO;

	glGenVertexArrays(1, &lightvao);
	glBindVertexArray(lightvao);

	glBindBuffer(GL_ARRAY_BUFFER, CUBEVBO);

	glGenBuffers(1, &lightEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// floor block
	GLuint floorVAO;
	GLuint floorEBO;

	glGenVertexArrays(1, &floorVAO);
	glBindVertexArray(floorVAO);

	glBindBuffer(GL_ARRAY_BUFFER, CUBEVBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, 0, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glGenBuffers(1, &floorEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floorEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//wall texture

	stbi_set_flip_vertically_on_load(true);
	unsigned int Walltextures;

	glGenTextures(1, &Walltextures);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Walltextures);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int Wwidth, Wheight, Wnrchannels;

	unsigned char* Wdata = stbi_load("wall.jpg", &Wwidth, &Wheight, &Wnrchannels, 0);


	if (Wdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Wwidth, Wheight, 0, GL_RGB, GL_UNSIGNED_BYTE, Wdata);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	else
	{
		std::cout << "failed to load wall data" << std::endl;
	}

	stbi_image_free(Wdata);

	//floor texture
	unsigned int  floortexture;
	glGenTextures(1, &floortexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, floortexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int Fwidth, Fheight, Fnrchannels;
	unsigned char* Fdata = stbi_load("wood.png", &Fwidth, &Fheight, &Fnrchannels, 0);

	if (Fdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Fwidth, Fheight, 0, GL_RGB, GL_UNSIGNED_BYTE, Fdata);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	else
	{
		std::cout << "failed to load floor data" << std::endl;
	}
	
	stbi_image_free(Fdata);

	//generation of floor vector coordinates

	std::vector <glm::vec3> floorcoors;
	int x_val = 10, z_val = 10;
	for (int i = 0;i < x_val;i++)
	{
		for (int j = 0;j < z_val;j++)
		{
			float posx = i * 1.0f;
			float posz = j * 1.0f;
			float posy = -1.0f;
			floorcoors.push_back(glm::vec3(posx, posy, posz));
		}
	}

	//testing roof
	int x_up = 10, z_up = 10;
	for (int i = 0;i < x_up;i++)
	{
		for (int j = 0;j < z_up;j++)
		{
			float posx = i * 1.0f;
			float posz = j * 1.0f;
			float posy = 5.0f;
			floorcoors.push_back(glm::vec3(posx, posy, posz));
		}
	}

	//wall pos
	std::vector <glm::vec3> wallcoors;
	int x_upw = 10, y_upw = 10;
	for (int i = 0;i < x_upw;i++)
	{
		for (int j = 0;j < y_upw;j++)
		{
			float posx = i * 1.0f;
			float posz = 1.0f;
			float posy = j * 1.0f;
			wallcoors.push_back(glm::vec3(posx, posy, posz));
		}
	}



	while (!glfwWindowShouldClose(window))
	{


		float currentframe = static_cast<float>(glfwGetTime());
		deltatime = currentframe - lastframe;
		lastframe = currentframe;

		//std::cout << camerafront.x << "," << camerafront.y << "," << camerafront.z << std::endl;
		std::cout << camerapos.x << "," << camerapos.y << "," << camerapos.z << std::endl;

		processInput(window);
		glClearColor(background_light.x, background_light.y, background_light.z, background_light.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, Walltextures);

		wall.useshader();
		wall.settexture("ourTexture", 0);
		//float lightscale = sin(glfwGetTime());
		//if (lightscale < 0)
		//{
		//	lightscale = -lightscale;
		//}
		float lightscale = 0.3;
		float multiplier = 4;

		wall.setvec3("lightColor", lightobjectcolor);
		wall.setvec3("objectColor", glm::vec3(0.5f, 0.5f, 0.5f));
		wall.setvec3("lightpos", lightpos);
		wall.setvec3("viewpos", camerapos);

		//attenuation values-
		wall.setvec3("attenval", glm::vec3(1.0f, 0.014f, 0.0007f));
		wall.setfloat("lightscale", lightscale);
		wall.setfloat("lightmultiplier", multiplier);

		glBindVertexArray(CUBEVAO);

		//camera

		glm::mat4 view = glm::lookAt(camerapos, camerapos + camerafront, cameraup);
		wall.setmat4("view", view);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(scwidth / scheight), 0.1f, 500.0f);
		wall.setmat4("projection", projection);

		for (int i = 0;i < x_val * z_val;i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, wallcoors[i]);

			float angle = 0;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			wall.setmat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		}

		//floor

		glBindTexture(GL_TEXTURE_2D, floortexture);

		floor.useshader();
		floor.settexture("ourTexture", 1);
		floor.setvec3("lightColor", lightobjectcolor);
		floor.setvec3("objectColor", glm::vec3(0.5f, 0.5f, 0.5f));
		floor.setvec3("lightpos", lightpos);
		floor.setvec3("viewpos", camerapos);

		floor.setvec3("attenval", glm::vec3(1.0f, 0.0014f, 0.000007f));
		floor.setfloat("lightscale", lightscale);
		floor.setfloat("lightmultiplier", multiplier);
		glBindVertexArray(floorVAO);

		floor.setmat4("view", view);
		floor.setmat4("projection", projection);

		for (int i = 0;i < x_val * z_val;i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, floorcoors[i]);

			float angle = 0;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			wall.setmat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		}


		//lightpos.x = 4 * sin(glfwGetTime());
		lightpos.y = 4 * sin(glfwGetTime());
		//lightpos.z = 2 * cos(glfwGetTime());

		light.useshader();
		light.setvec3("color", lightobjectcolor);
		light.setmat4("view", view);
		light.setmat4("projection", projection);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightpos);
		model = glm::scale(model, glm::vec3(lightscale));
		light.setmat4("model", model);
		glBindVertexArray(lightvao);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);





		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	wall.deleteshader();
	glDeleteTextures(1, &Walltextures);
	glDeleteVertexArrays(1, &CUBEVAO);
	glDeleteBuffers(1, &CUBEVBO);
	glDeleteBuffers(1, &CUBEEBO);

	light.deleteshader();
	glDeleteVertexArrays(1, &lightvao);
	glDeleteBuffers(1, &lightEBO);

	floor.deleteshader();
	glDeleteVertexArrays(1, &floorVAO);
	glDeleteBuffers(1, &floorEBO);
	glDeleteTextures(1, &floortexture);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeedvertical = 4.5 * deltatime;
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