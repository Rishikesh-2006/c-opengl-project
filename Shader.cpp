#include "Shader.h"



Shader::Shader(const char* vertexpath, const char* fragmentpath)
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

}


void Shader::useshader()
{
	glUseProgram(shaderprogram);
}


void Shader::deleteshader()
{
	glDeleteProgram(shaderprogram);
}



void Shader::setvec3(const std::string &name,const glm::vec3 &value)
{
	glUniform3fv(glGetUniformLocation(shaderprogram, name.c_str()), 1,&value[0]);
}


void Shader::setmat4(const std::string& name, const glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderprogram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


void Shader::setint(const std::string& name, const int value)
{
	glUniform1i(glGetUniformLocation(shaderprogram, name.c_str()), value);
}


void Shader::setfloat(const std::string& name, const float value)
{
	glUniform1f(glGetUniformLocation(shaderprogram, name.c_str()), value);
}

void Shader::settexture(const std::string& name, const int loc)
{
	glUniform1i(glGetUniformLocation(shaderprogram, name.c_str()), loc);
}