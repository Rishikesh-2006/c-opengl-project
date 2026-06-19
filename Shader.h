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

	Shader(const char* vertexpath, const char* fragmentpath);
	//void activateshader(const char* vertexpath,const char* fragmentpath);

	void useshader();

	void deleteshader();

	void setvec3(const std::string &name,const glm::vec3 &value);

	void setmat4(const std::string& name, const glm::mat4 mat);

	void setint(const std::string& name, const int value);

	void setfloat(const std::string& name, const float value);

	void settexture(const std::string& name, const int loc);
};

