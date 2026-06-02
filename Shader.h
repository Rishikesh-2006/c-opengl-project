#pragma once
#include <glad/glad.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>




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

	unsigned int shprgm();

};

