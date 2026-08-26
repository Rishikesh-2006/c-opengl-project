#include <stb/stb_image.h>
#include <iostream>
#include "Shader.h"
#include "object.h"
#include <string.h>
#include "camera.h"
#include "water.h"

int scheight = 1080;
int scwidth = 1920;
unsigned int depthwidth = 4096, depthheight = 4096;

float deltatime = 0.0f;
float lastframe = 0.0f;

//lightobject
glm::vec3 lightpos(-22.0f, 18.0f, 7.0f);

glm::vec4 background_light = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f);
std::vector <glm::vec3> waterpos = { glm::vec3(1.0f, -3.0f, -20.0f) };

//glm::vec4 background_light = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

//functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int set_texture(GLenum Tex_num, const char* name, GLenum val1, GLenum val2);
void shadowcalc(std::vector <glm::vec3>& vector, object& shadowobject, unsigned int& cubeVAO,unsigned int idx_size);
void Make_Structure(std::vector <glm::vec3>& array, glm::vec3 start, float distance, float num);


float player_factor = 0.5;
float speed = 40.0f;
int main()
{

	obj_info phy_obja, phy_objb;

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
	wallcoors.push_back(glm::vec3(15.0f, 7.0f, 15.0f));
	std::vector <glm::vec3> blockcoors;
	blockcoors.push_back(glm::vec3(15.0f, 7.0f, 15.0f));

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

	for (int i = 0;i < x_wall;i++)
	{
		for (int j = 0;j < y_wall;j++)
		{
			float posx = 29.0f;
			float posy = j * 1.0f;
			float posz = i * 1.0f;
			wallcoors.push_back(glm::vec3(posx, posy, posz));
		}
	}

	for (int i = 0;i < x_wall;i++)
	{
		for (int j = 0;j < y_wall;j++)
		{
			float posx = 0.0f;
			float posy = j * 1.0f;
			float posz = i * 1.0f;
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

	//collision objects
	phy_obja.position = glm::vec3(16.0f, 14.0f, 16.0f);
	phy_objb.position = glm::vec3(16.0f, 8.0f, 16.0f);
	phy_obja.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	phy_objb.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	phy_obja.mass = 1.0f;
	phy_objb.mass = 1.0f;

	std::vector <obj_info> informations;
	int x_value = 14, y_value = 12;

	for (int i = 13; i < x_value; i++)
	{
		for (int j = 10; j < y_value; j++)
		{
			float valx = i * 1.0f;
			float valy = j * 1.0f;
			float valz = 7.0f;
			informations.push_back({ glm::vec3(0.0f, 8.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(valx, valy, valz),1.0f });
		}
	}


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(scwidth, scheight, "opengl", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "failed to open window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//loading opengl using glad

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//shader class to initialize and combine vertex and fragement shader
	object wall("wall.vert", "wall.frag");
	object light("lightobject.vert", "lightobject.frag");
	object floor("wall.vert", "wall.frag");
	object shadow("shadow.vert", "shadow.frag");
	object phy("phy_obj.vert", "phy_obj.frag");
	water water("water.vert", "water.frag");

	camera camera;

	camera.set_caminputs(window);


	//this ensures the faces on the front are shown and the back ones are hidden

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	//std::cout<<glGetString(GL_RENDERER)<<std::endl;
	

	//vertex buffers , arrays

	//main cube object

	unsigned int CUBEVBO;

	wall.set_VBO_object(CUBEVBO);

	unsigned int CUBEVAO = wall.VAO;
	unsigned int CUBEEBO = wall.EBO;

	//lightobject

	light.set_object(CUBEVBO, true);
	unsigned int lightVAO = light.VAO;
	unsigned int lightEBO = light.EBO;


	//floor 

	unsigned int floorVAO, floorEBO;
	floor.set_object(CUBEVBO, false);

	floorVAO = floor.VAO;
	floorEBO = floor.EBO;

	//collision objects

	unsigned int phyVAO, phyEBO;
	phy.set_object(CUBEVBO, false);

	phyVAO = phy.VAO;
	phyEBO = phy.EBO;

	//water
	

	std::vector<float> water_vertices;
	std::vector<unsigned int> water_indices;
	int grid_size = 500;

	float size = 1.0f;
	for (int i = 0; i <= grid_size; ++i)
	{
		for (int j = 0; j <= grid_size; ++j)
		{
			float xpos = ((i / grid_size) - 0.5f) * size;
			float zpos = ((j / grid_size) - 0.5f) * size;

			water_vertices.push_back(xpos);
			water_vertices.push_back(1.0f);
			water_vertices.push_back(zpos);

			water_vertices.push_back(0.0f);
			water_vertices.push_back(1.0f);
			water_vertices.push_back(0.0f);

			float u = i / grid_size;
			float v = j / grid_size;

			water_vertices.push_back(u);
			water_vertices.push_back(v);
		}

	}

	for (int z = 0; z < grid_size; ++z) {
		for (int x = 0; x < grid_size; ++x) {
			int topLeft = z * (grid_size + 1) + x;
			int topRight = topLeft + 1;
			int bottomLeft = (z + 1) * (grid_size + 1) + x;
			int bottomRight = bottomLeft + 1;

			// triangle 1
			water_indices.push_back(topLeft);
			water_indices.push_back(bottomLeft);
			water_indices.push_back(topRight);

			// triangle 2
			water_indices.push_back(topRight);
			water_indices.push_back(bottomLeft);
			water_indices.push_back(bottomRight);
		}
	}

	water.setvertexdata(water_vertices, water_indices,scwidth,scheight);

	unsigned int waterVAO, waterVBO, waterEBO;
	water.set_water_objects(waterVBO);

	waterVAO = water.VAO;
	water.EBO = water.EBO;
	//depth map

	unsigned int depthmapFBO,depthmap;

	shadow.set_shadowFBO(depthmapFBO, depthmap, depthwidth, depthheight);

	//Textures
	//set orientation
	stbi_set_flip_vertically_on_load(true);

	//wall texture

	unsigned int Walltextures = set_texture(GL_TEXTURE0, "Textures/bricks.png", GL_RGB, GL_RGB);

	//floor texture

	unsigned int floortexture = set_texture(GL_TEXTURE1, "Textures/wooden floor.png", GL_RGB, GL_RGB);

	//others
	unsigned int high_floor = set_texture(GL_TEXTURE2, "Textures/rr.png", GL_RGBA, GL_RGBA);

	unsigned int brickwall = set_texture(GL_TEXTURE4, "Textures/brickwall.jpg", GL_RGB, GL_RGB);

	unsigned int brickwall_normal = set_texture(GL_TEXTURE5, "Textures/brickwall_normal.jpg", GL_RGB, GL_RGB);
	//water texture

	unsigned int water1 = set_texture(GL_TEXTURE6, "Textures/normal_water.png", GL_RGB, GL_RGB);

	unsigned int water2 = set_texture(GL_TEXTURE7, "Textures/water_texture.png", GL_RGB, GL_RGB);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Walltextures);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, floortexture);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, high_floor);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, depthmap);


	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, brickwall);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, brickwall_normal);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, water1);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, water2);




	glm::vec3 gravity = glm::vec3(0.0f, 0.0f, 0.0f);
	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 view  = camera.set_view();
		glm::mat4 projection = camera.set_projection();

		float currentframe = static_cast<float>(glfwGetTime());
		deltatime = currentframe - lastframe;

		int fps = 1 / deltatime;
		std::string sfps = std::to_string(fps);
		const char* cfps = sfps.c_str();
		glfwSetWindowTitle(window, cfps);
		lastframe = currentframe;

		//water

		water.useshader();


		water.settexture("water_texture", 7);
		water.setmat4("view", view);
		water.setmat4("projection", projection);
		glm::vec3 axis = glm::vec3(1.0f, 0.3f, 0.5f);

		glm::mat4 wmodel = glm::mat4(1.0f);
		wmodel = glm::translate(wmodel, glm::vec3(1.0f, -3.0f, -20.0f));
		//float angle = 0;
		//wmodel = glm::rotate(wmodel, float(14.138), glm::vec3(1.0f, 0.0f, 0.0f));
		wmodel = glm::scale(wmodel, glm::vec3(40.0f, 1.0f, 30.0f));
		water.setmat4("model", wmodel);
		glBindVertexArray(waterVAO);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(water_indices.size()), GL_UNSIGNED_INT, 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



		phy_obja.acceleration = glm::vec3(0.0f, 9.8f, 0.0f);
		phy_objb.acceleration = glm::vec3(0.0f, 9.8f, 0.0f);


		//campos

		glm::mat4 shadowprojection = glm::ortho(-30.0, 30.0, -30.00, 30.00, 0.1, 60.0);
		glm::mat4 shadowview = glm::lookAt(lightpos, glm::vec3(15.0f, 7.5f, 15.0f), glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 sh_projection = shadowprojection * shadowview;

		//shadow

		glBindFramebuffer(GL_FRAMEBUFFER, depthmapFBO);
		glViewport(0, 0, depthwidth, depthheight);
		glClear(GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);

		shadow.useshader();

		shadow.setmat4("lightprojection", sh_projection);
		shadowcalc(blockcoors, shadow, CUBEVAO,wall.index_size);
		//shadowcalc(waterpos, shadow, waterVAO,sizeof(water_indices));

		glCullFace(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);



		glViewport(0, 0, scwidth, scheight);
		glClearColor(background_light.x, background_light.y,
			background_light.z, background_light.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		//wall


		wall.set_in_loop("ourTexture", 4, lightpos, camera.camerapos);
		wall.setmat4("lightprojection", sh_projection);


		//camera
		wall.setmat4("view", view);

		wall.setmat4("projection", projection);


		glBindVertexArray(floorVAO);
		for (glm::vec3& i : wallcoors)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, i);

			float angle = 0;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			wall.setmat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		}


		//floor

		floor.set_in_loop("ourTexture", 4,lightpos, camera.camerapos);
		floor.setmat4("lightprojection", sh_projection);

		floor.setmat4("view", view);
		floor.setmat4("projection", projection);

		glBindVertexArray(floorVAO);

		for (glm::vec3& i : floorcoors)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, i);

			float angle = 0;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			floor.setmat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		}

		//physics objects

		phy.useshader();
		phy.setmat4("view", view);
		phy.setmat4("projection", projection);
		phy.setvec2("uResolution", glm::vec2(scwidth, scheight));
		glBindVertexArray(phyVAO);
		for (obj_info &i : informations)
		{
			glm::mat4 p1model = glm::mat4(1.0f);
			p1model = glm::translate(p1model, i.position);
			float angle1 = 0;
			p1model = glm::rotate(p1model, glm::radians(angle1), glm::vec3(1.0f, 0.3f, 0.5f));
			phy.setmat4("model", p1model);
			phy.setvec3("color", glm::vec3(sin(glfwGetTime()), 1.0f, 1.0f));

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		}
		phy.multicollision(informations,camera.camerapos,deltatime);
		
		//light object

		light.set_light_in_loop(lightpos, lightVAO, view, projection);

			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			{
				lightpos = glm::vec3(camera.camerapos.x, camera.camerapos.y - 1.0f, camera.camerapos.z);
			}

			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
			{
				wall.set_lightmultiplier(0.5f);
				floor.set_lightmultiplier(0.5f);
			}

			if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
			{
				wall.set_lightmultiplier(-0.5f);
				floor.set_lightmultiplier(-0.5f);
			}

			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			{
				wall.set_lightcolor(0.5f);
				floor.set_lightcolor(0.5f);
				light.set_lightcolor(0.5f);
			}

			if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
			{
				wall.set_lightcolor(-0.5f);
				floor.set_lightcolor(-0.5f);
				light.set_lightcolor(-0.5f);
			}


			camera.processInput(window,speed,deltatime);


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

		phy.deleteshader();
		glDeleteVertexArrays(1, &phyVAO);
		glDeleteBuffers(1, &phyEBO);

		water.deleteshader();
		water.cleanUp();

		glDeleteTextures(1, &brickwall);
		glDeleteTextures(1, &brickwall_normal);

		glfwDestroyWindow(window);
		glfwTerminate();
		return 0;
	}

unsigned int set_texture(GLenum Tex_num, const char* name, GLenum val1, GLenum val2)
{
	unsigned int texture;


	glGenTextures(1, &texture);
	glActiveTexture(Tex_num);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	int Fwidth, Fheight, Fnrchannels;
	unsigned char* Fdata = stbi_load(name, &Fwidth, &Fheight, &Fnrchannels, 0);
	if (Fdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, val1, Fwidth, Fheight, 0, val2, GL_UNSIGNED_BYTE, Fdata);
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

void shadowcalc(std::vector <glm::vec3>& vector, object& shadowobject, unsigned int& cubeVAO,unsigned int idx_size)
{
	glBindVertexArray(cubeVAO);

	for (glm::vec3& i : vector)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, i);

		float angle = 0;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		shadowobject.setmat4("model", model);

		glDrawElements(GL_TRIANGLES,idx_size, GL_UNSIGNED_INT, 0);


	}


}

//reuse this for block generation 

void Make_Structure(std::vector <glm::vec3>& array, glm::vec3 start, float distance, float num)
{

	for (float i = 0;i < num;i += 1.0f)
	{
		start = glm::vec3(start.x + distance, start.y + distance, start.z);
		for (float j = 0;j < num;j += 1.0f)
		{
			array.push_back(start);
			array.push_back(glm::vec3(start.x, start.y - 1.0f, start.z));
			array.push_back(glm::vec3(start.x, start.y - 2.0f, start.z));
			array.push_back(glm::vec3(start.x + 1.0f, start.y, start.z));
			array.push_back(glm::vec3(start.x + 1.0f, start.y - 2.0f, start.z));
			array.push_back(glm::vec3(start.x + 2.0f, start.y, start.z));
			array.push_back(glm::vec3(start.x + 2.0f, start.y - 1.0f, start.z));
			array.push_back(glm::vec3(start.x + 2.0f, start.y - 2.0f, start.z));
		}
	}
}