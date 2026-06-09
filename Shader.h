#pragma once
#include <glad/glad.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




class Shader
{
	unsigned int shaderprogram;
public:
	// for activating shader in the loop
	void activateshader(const char* vertexpath,const char* fragmentpath);
	//to use the shader
	void useshader();
	// deletion of shader after running game code to free up memory
	void deleteshader();

	unsigned int getshdr();

	void setvec3(const std::string &name,const glm::vec3 &value);

	void setmat4(const std::string& name, const glm::mat4 mat);

};

