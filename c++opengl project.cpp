#include <stb/stb_image.h>
#include <iostream>
#include "Shader.h"
#include "object.h"
#include <string.h>


int scheight = 800;
int scwidth = 800;

//camera vals
glm::vec3 camerapos = { -35.75f, 7.48f, 15.52f };
glm::vec3 camerafront = { 0.99f, -0.07f, 0.008f };
glm::vec3 cameraup = { 0.0f, 1.0f ,0.0f };

bool firstmouse = true;
float yaw = 0.0f;
float pitch = 0.0f;
float lastx = scwidth / 2.0f;
float lasty = scheight / 2.0f;
float fov = 45.0f;


float deltatime = 0.0f;
float lastframe = 0.0f;

//lightobject
glm::vec3 lightpos(15.0f, 12.0f, 10.0f);
glm::vec3 lightobjectcolor(1.0f, 1.0f, 1.0f);
glm::vec4 background_light = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f);
//glm::vec4 background_light = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

//functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposin, double yposin);
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int set_texture(GLenum Tex_num, const char* name, GLenum val);
void shadowcalc(std::vector <glm::vec3>& vector, object& object);


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

	float sq_vertex[] = {
	0.5f,-0.5f,0.0f,
	0.5f,0.5f,0.0f,
	-0.5f,-0.5f,0.0f,
	-0.5f,0.5f,0.0f
	};

	unsigned int sq_indice[] = {
		0,1,2,
		3,2,1
	};

	//wall pos
	std::vector <glm::vec3> wallcoors;
	int x_wall = 30, y_wall = 15;
	for (int i = 0;i < x_wall;i++)
	{
		for (int j = 0;j < y_wall;j++)
		{
			float posx = i * 1.0f;
			float posy = j * 1.0f;
			float posz = 0.0f;
			wallcoors.push_back(glm::vec3(posx, posy, posz));
		}
	}
	//wallcoors.push_back(glm::vec3(15.0f, 5.0f,4.0f));
	//wallcoors.push_back(glm::vec3(14.0f, 5.0f, 4.0f));
	for (int i = 0;i < x_wall;i++)
	{
		for (int j = 0;j < y_wall;j++)
		{
			float posx = i * 1.0f;
			float posy = j * 1.0f;
			float posz = 29.0f;
			wallcoors.push_back(glm::vec3(posx, posy, posz));
		}
	}

	//floor pos
	std::vector <glm::vec3> floorcoors;
	int x_floor = 30, z_floor = 30;
	for (int i = 0;i < x_floor;i++)
	{
		for (int j = 0; j < z_floor;j++)
		{
			float posxf = i * 1.0f;
			float posyf = -1.0f;
			float poszf = j * 1.0f;
			floorcoors.push_back(glm::vec3(posxf, posyf, poszf));
		}
	}

	for (int i = 0;i < x_floor;i++)
	{
		for (int j = 0; j < z_floor;j++)
		{
			float posxf = i * 1.0f;
			float posyf = 15.0f;
			float poszf = j * 1.0f;
			floorcoors.push_back(glm::vec3(posxf, posyf, poszf));
		}
	}
	//water

	/*std::vector <glm::vec3> watercoors;
	int x_water = 50, z_water = 50;
	for (int i = -50;i < x_water;i++)
	{
		for (int j = 0; j < z_water;j++)
		{
			float wposx = i * 1.0f;
			float wposy = 0.0f;
			float wposz = j * 1.0f;
			watercoors.push_back(glm::vec3(wposx, wposy, wposz));
		}
	}
	*/

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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//loading opengl using glad

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	//shader class to initialize and combine vertex and fragement shader
	object wall("wall.vert", "wall.frag");
	object light("lightobject.vert", "lightobject.frag");
	object floor("floor.vert", "floor.frag");
	object sq("water.vert", "water.frag");
	//object water("floor.vert", "floor.frag");
	object shadow("shadow.vert", "shadow.frag");
	//this ensures the faces on the front are shown and the back ones are hidden

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	//vertex buffers , arrays

	//main cube object

	unsigned int CUBEVBO;

	wall.set_VBO_object(CUBEVBO, vertices, sizeof(vertices), indices, sizeof(indices));

	unsigned int CUBEVAO = wall.VAO;
	unsigned int CUBEEBO = wall.EBO;

	//lightobject

	light.set_object(CUBEVBO, indices, sizeof(indices), true);
	unsigned int lightVAO = light.VAO;
	unsigned int lightEBO = light.EBO;


	//floor 

	unsigned int floorVAO, floorEBO;
	floor.set_object(CUBEVBO, indices, sizeof(indices), false);

	floorVAO = floor.VAO;
	floorEBO = floor.EBO;

	//water block

	/*unsigned int waterVAO, waterEBO;
	water.set_object(CUBEVBO, indices, sizeof(indices), false);

	waterVAO = water.VAO;
	waterEBO = water.EBO;
	*/
	//square
	

	unsigned int sqVBO, sqVAO=0, sqEBO;

	glGenBuffers(1, &sqVBO);
	glBindVertexArray(sqVAO);

	glBindBuffer(GL_ARRAY_BUFFER, sqVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sq_vertex), sq_vertex, GL_STATIC_DRAW);
	glGenBuffers(1, &sqEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sqEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sq_indice), sq_indice, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//depth map

	unsigned int depthmapFBO;
	glGenFramebuffers(1, &depthmapFBO);

	unsigned int depthwidth = 1024, depthheight = 1024;
	unsigned int depthmap;
	glGenTextures(1, &depthmap);
	glBindTexture(GL_TEXTURE_2D, depthmap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, depthwidth, depthheight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float clampcolor[] = {1.0f,1.0f,1.0f,1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampcolor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthmapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthmap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glm::mat4 shadowprojection = glm::ortho(-10.0, 10.0, -10.00, 10.00, 0.1, 10.0);

	glBindFramebuffer(GL_FRAMEBUFFER, depthmapFBO);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, depthwidth, depthheight);
	glBindVertexArray(CUBEVAO);
	shadowcalc(wallcoors, shadow);
	glBindVertexArray(floorVAO);
	shadowcalc(floorcoors, shadow);
	//shadowcalc(watercoors, shadow);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	


	glViewport(0, 0, scwidth, scheight);
	//Textures
	//set orientation
	stbi_set_flip_vertically_on_load(true);

	//wall texture

	unsigned int Walltextures = set_texture(GL_TEXTURE0, "Textures/bricks.png", GL_RGB);

	//floor texture

	unsigned int floortexture = set_texture(GL_TEXTURE1, "Textures/wooden floor.png", GL_RGB);

	//water texture

	unsigned int watertexture = set_texture(GL_TEXTURE2, "Textures/test_water.png", GL_RGBA);
	
	
	float velocity = 0.0f;
	float accln = 9.81f;
	while (!glfwWindowShouldClose(window))
	{

		float currentframe = static_cast<float>(glfwGetTime());
		deltatime = currentframe - lastframe;

			int fps = 1 / deltatime;
			std::string sfps = std::to_string(fps);
			const char* cfps = sfps.c_str();
			glfwSetWindowTitle(window, cfps);
			lastframe = currentframe;


		//fpscalc
		
		//std::cout << camerafront.x << "," << camerafront.y << "," << camerafront.z << std::endl;
		//std::cout << camerapos.x << "," << camerapos.y << "," << camerapos.z << std::endl;


		processInput(window);
		glClearColor(background_light.x, background_light.y, background_light.z, background_light.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		//glBindTexture(GL_TEXTURE_2D, watertexture);

		

		//lightobjectcolor.x = sin(glfwGetTime());
		//lightobjectcolor.y = cos(glfwGetTime());
		//lightobjectcolor.z = 2 * cos(glfwGetTime());


		//shadow
		glBindTexture(GL_TEXTURE_2D, depthmap);

		shadow.useshader();
		glm::mat4 shadowview = glm::lookAt(lightpos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 sh_projection = shadowprojection * shadowview;
		shadow.setmat4("lightprojection", sh_projection);

		glBindFramebuffer(GL_FRAMEBUFFER, depthmapFBO);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, scwidth, scheight);
		glBindVertexArray(CUBEVAO);
		shadowcalc(wallcoors, shadow);
		glBindVertexArray(floorVAO);
		shadowcalc(floorcoors, shadow);
		//shadowcalc(watercoors, shadow);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		//wall
		glBindTexture(GL_TEXTURE_2D, Walltextures);

		wall.set_in_loop(wall, "ourTexture", 0, lightobjectcolor, lightpos, camerapos);
		wall.setmat4("lightprojection", sh_projection);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, depthmap);
		glBindVertexArray(CUBEVAO);

		//camera

		glm::mat4 view = glm::lookAt(camerapos, camerapos + camerafront, cameraup);
		wall.setmat4("view", view);

		glm::mat4 projection = glm::perspective(fov, float(scwidth / scheight), 0.1f, 400.0f);
		wall.setmat4("projection", projection);


		for (glm::vec3 &i : wallcoors)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, i);

			float angle = 0;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			wall.setmat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		}


		//floor
		glBindTexture(GL_TEXTURE_2D, floortexture);

		floor.set_in_loop(floor, "ourTexture", 1, lightobjectcolor, lightpos, camerapos);
		glBindVertexArray(floorVAO);

		floor.setmat4("view", view);
		floor.setmat4("projection", projection);

		for (int i = 0;i < x_floor * z_floor * 2;i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, floorcoors[i]);

			float angle = 0;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			floor.setmat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		}

		//water block

/*		water.set_in_loop(water, "ourTexture", 2, lightobjectcolor, lightpos, camerapos);
		glBindVertexArray(waterVAO);

		water.setmat4("view", view);
		water.setmat4("projection", projection);

		for (glm::vec3 i : floorcoors)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model,i);

			float angle = 0;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			floor.setmat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		}
		*/

		//testing movement in circular motion

		//lightpos.x = 7 + 4 * sin(glfwGetTime());
		lightpos.y = 4*sin(glfwGetTime());
		//lightpos.z = 15+4 * cos(glfwGetTime());

		//velocity += accln * deltatime;
		//lightpos.y -= velocity * deltatime;

		//if (lightpos.y < 0.5f * light.lightscale - 0.5f)
		//{

			//lightpos.y = 0.5f * light.lightscale - 0.5f;
			//velocity = -velocity * 0.70f;
		//}

		//std::cout << velocity << std::endl;

		//light 
		//glm::vec3 axis = glm::vec3(1.0f, 0.3f, 0.5f);

		light.useshader();
		light.setvec3("color", lightobjectcolor);
		light.setmat4("view", view);
		light.setmat4("projection", projection);


		//std::cout << axis.x<<"," << axis.y<<","<< axis.z << std::endl;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightpos);
		//model = glm::rotate(model, 4*sin(float(glfwGetTime())),axis);
		model = glm::scale(model, glm::vec3(light.lightscale));
		light.setmat4("model", model);
		glBindVertexArray(lightVAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		//square

		sq.useshader();
		sq.setvec3("color", glm::vec3(0.0f, 0.0f, 1.0f));
		sq.setmat4("view", view);
		sq.setmat4("projection", projection);

		glm::vec3 axis = glm::vec3(1.0f, 0.3f, 0.5f);

		glm::mat4 sqmodel = glm::mat4(1.0f);
		sqmodel = glm::translate(sqmodel, glm::vec3(1.0f,1.0f,-20.0f));

		float angle = 0;
		//std::cout << glfwGetTime() << std::endl;
		sqmodel = glm::rotate(sqmodel,float(14.138), glm::vec3(1.0f, 0.0f, 0.0f));
		sqmodel = glm::scale(sqmodel, glm::vec3(40.0f, 30.0f,0.0f));
		sq.setmat4("model", sqmodel);
		//glBindVertexArray(sqVAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	wall.deleteshader();
	glDeleteTextures(1, &Walltextures);
	glDeleteVertexArrays(1, &CUBEVAO);
	glDeleteBuffers(1, &CUBEVBO);
	glDeleteBuffers(1, &CUBEEBO);

	light.deleteshader();
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightEBO);

	floor.deleteshader();
	glDeleteVertexArrays(1, &floorVAO);
	glDeleteBuffers(1, &floorEBO);
	glDeleteTextures(1, &floortexture);

	sq.deleteshader();
	glDeleteVertexArrays(1, &sqVAO);
	glDeleteBuffers(1, &sqVBO);
	glDeleteBuffers(1, &sqEBO);

	/*water.deleteshader();
	glDeleteVertexArrays(1, &waterVAO);
	glDeleteBuffers(1, &waterEBO);
	glDeleteTextures(1, &watertexture);
	*/

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstmouse)
	{
		lastx = xpos;
		lasty = ypos;
		firstmouse = false;
	}

	float xoffset = xpos - lastx;
	float yoffset = lasty - ypos; // reversed since y-coordinates go from bottom to top
	lastx = xpos;
	lasty = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

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

	const float cameraSpeed = 80.0f*deltatime; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camerapos += cameraSpeed * camerafront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camerapos -= cameraSpeed * camerafront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camerapos -= glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camerapos += glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeed;

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset*0.06;

	if (fov < 1.0f)
	{
		fov = 1.0f;
	}
	if (fov > 45.0f)
	{
		fov = 45.0f;
	}
}


unsigned int set_texture(GLenum Tex_num, const char* name, GLenum val)
{
	unsigned int texture;


	glGenTextures(1, &texture);
	glActiveTexture(Tex_num);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int Fwidth, Fheight, Fnrchannels;
	unsigned char* Fdata = stbi_load(name, &Fwidth, &Fheight, &Fnrchannels, 0);
	if (Fdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, val, Fwidth, Fheight, 0, val, GL_UNSIGNED_BYTE, Fdata);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	else
	{
		std::cout << "failed to load floor data" << std::endl;
	}

	stbi_image_free(Fdata);

	return texture;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	glViewport(0, 0, width, height);
}

void shadowcalc(std::vector <glm::vec3> &vector,object &object)
{
	for (glm::vec3 i : vector)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, i);

		float angle = 0;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		object.setmat4("model", model);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	}
}