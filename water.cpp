#include "water.h"

void water::set_water_objects(unsigned int& waterVBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &waterVBO);
	glGenBuffers(1, &EBO);


	glBindBuffer(GL_ARRAY_BUFFER, waterVBO);
	glBufferData(GL_ARRAY_BUFFER, water_vertices.size() * sizeof(float), water_vertices.data(), GL_STATIC_DRAW);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, water_indices.size() * sizeof(unsigned int), water_indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void water::set_watercoors(float grid_size)
{
	float size = 1.0f;
	for (int i = 0; i <= grid_size; ++i)
	{
		for (int j = 0; j <= grid_size; ++j)
		{
			float xpos = ((i / grid_size) - 0.5f) * size;
			float zpos = ((j / grid_size) - 0.5f) * size;

			this->water_vertices.push_back(xpos);
			this->water_vertices.push_back(1.0f);
			this->water_vertices.push_back(zpos);

			this->water_vertices.push_back(0.0f);
			this->water_vertices.push_back(1.0f);
			this->water_vertices.push_back(0.0f);

			float u = i / grid_size;
			float v = j / grid_size;

			this->water_vertices.push_back(u);
			this->water_vertices.push_back(v);
		}

	}

	for (int z = 0; z < grid_size; ++z) {
		for (int x = 0; x < grid_size; ++x) {
			int topLeft = z * (grid_size + 1) + x;
			int topRight = topLeft + 1;
			int bottomLeft = (z + 1) * (grid_size + 1) + x;
			int bottomRight = bottomLeft + 1;

			// triangle 1
			this->water_indices.push_back(topLeft);
			this->water_indices.push_back(bottomLeft);
			this->water_indices.push_back(topRight);

			// triangle 2
			this->water_indices.push_back(topRight);
			this->water_indices.push_back(bottomLeft);
			this->water_indices.push_back(bottomRight);
		}
	}
	unsigned int waterVBO;

	set_water_objects(waterVBO);
}

void water::set_visual(water &water,glm::mat4 view , glm::mat4 projection,glm::vec3 lightobjectcolor,glm::vec3 lightpos,glm::vec3 camerapos,glm::mat4 sh_projection,unsigned int waterVAO,unsigned int fbo)
{
	//in construction
	
	water.useshader();
	//water.settexture("Texture", 6);
	//water.settexture("shadowmap", 3); //set to shadowtexture
	//water.setvec3("lightColor", lightobjectcolor);
	water.setvec3("color", glm::vec3(0.0f, 0.0f, 0.5f));
	water.settexture("reflecttexture", 6);
	//water.setvec3("lightpos", lightpos);
	//water.setvec3("viewpos", camerapos);
	//water.setmat4("lightprojection", sh_projection);

	//attenuation values-
	//water.setvec3("attenval", glm::vec3(1.0f, 0.014f, 0.0007f));
	//water.setfloat("lightscale", lightscale);
	//water.setfloat("lightmultiplier", multiplier);

	water.setmat4("view", view);
	water.setmat4("projection", projection);
	//water.setfloat("time", glfwGetTime());
	glm::vec3 axis = glm::vec3(1.0f, 0.3f, 0.5f);

	glm::mat4 wmodel = glm::mat4(1.0f);
	//1.0f, -3.0f, -20.0f
	//wmodel = glm::translate(wmodel, glm::vec3(camera.camerapos.x, camera.camerapos.y-15.0f, camera.camerapos.z));
	wmodel = glm::translate(wmodel, glm::vec3(1.0f, -3.0f, -20.0f));
	float angle = 0;
	//wmodel = glm::rotate(wmodel, float(14.138), glm::vec3(1.0f, 0.0f, 0.0f));
	wmodel = glm::scale(wmodel, glm::vec3(400.0f, 1.0f, 300.0f));
	water.setmat4("model", wmodel);
	glBindVertexArray(waterVAO);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(water_indices.size()), GL_UNSIGNED_INT, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


unsigned int water::set_shader(const char* vertexpath,const char* fragmentpath)
{
	std::string vertexsource;
	std::string fragmentsource;
	std::ifstream vertexopen;
	std::ifstream fragmentopen;

	vertexopen.open(vertexpath);
	fragmentopen.open(fragmentpath);

	std::stringstream vertexstream, fragmentstream;

	vertexstream << vertexopen.rdbuf();
	fragmentstream << fragmentopen.rdbuf();

	vertexopen.close();
	fragmentopen.close();

	vertexsource = vertexstream.str();
	fragmentsource = fragmentstream.str();

	const char* vertexsrc = vertexsource.c_str();
	const char* fragmentsrc = fragmentsource.c_str();



	unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexsrc, NULL);
	int successv;
	char inflog[512];
	glCompileShader(vertexshader);
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &successv);

	if (!successv)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, inflog);
		std::cout << "vertex shader error - " << inflog << std::endl;

	}


	unsigned int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentsrc, NULL);
	int successf;
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &successf);
	glCompileShader(fragmentshader);
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &successf);

	if (!successv)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, inflog);
		std::cout << "fragment shader error - " << inflog << std::endl;

	}

	shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);
	glLinkProgram(shaderprogram);

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	return shaderprogram;

}

unsigned int water::framebuffer()
{
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return framebuffer;
}

unsigned int water::framebuffertexture(int width, int height)
{
	unsigned int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0,GL_RGB,GL_UNSIGNED_INT,NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	return texture;
}

unsigned int water::depthTEXTURE(int width, int height)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
	return texture;
}

unsigned int water::renderbuffer(int width, int height)
{
	unsigned int depthbuffer;
	glGenRenderbuffers(1, &depthbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,width,height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
	return depthbuffer;
}

void water::bindframebuffer(unsigned int framebuffer, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, width, height);
}

void water::UNbindframebuffer(int width, int height)
{
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glViewport(0, 0, width, height);
}

void water::setfbo()
{
	
	framebufferid = framebuffer();
	textureid = framebuffertexture(reflection_width, reflection_height);
	depthid = depthTEXTURE(reflection_width, reflection_height);
	UNbindframebuffer(scwidth, scheight);
}

void water::bindfbo()
{
	bindframebuffer(framebufferid, reflection_width, reflection_height);
}

void water::set_resolution(int width, int height)
{
	this->scwidth = width;
	this->scheight = height;
}

void water::cleanbuffers()
{
	glDeleteFramebuffers(1, &framebufferid);
	glDeleteRenderbuffers(1, &depthid);
	glDeleteTextures(1, &textureid);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
}