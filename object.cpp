#include "object.h"


void object::set_object(unsigned int& VBO, unsigned int* indices, int indices_size, bool islightsrc)
{


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if (islightsrc == true)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	else
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, 0, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(3);
	}

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

	//this->VAO = VAO;
	//this->EBO = EBO;

	//std::cout << VAO << "," << EBO << ","<<VBO<<std::endl;
}

void object::set_VBO_object(unsigned int& VBO, float* vertices, int vertice_size, unsigned int* indices, int indice_size)
{
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertice_size, vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_size, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, 0, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);



	//this->VAO = VAO;
	//this->EBO = EBO;
	//std::cout << VAO << "," << EBO << "," << VBO << std::endl;

}

void object::set_in_loop(std::string textureloc, int num, glm::vec3 lightobjectcolor, glm::vec3 lightpos, glm::vec3 camerapos)
{
	useshader();
	settexture(textureloc, num);

	setvec3("lightColor", lightobjectcolor);
	setvec3("objectColor", glm::vec3(0.5f, 0.5f, 0.5f));
	setvec3("lightpos", lightpos);
	setvec3("viewpos", camerapos);

	//attenuation values-
	setvec3("attenval", glm::vec3(1.0f, 0.014f, 0.0007f));
	setfloat("lightscale", lightscale);
	setfloat("lightmultiplier", multiplier);

}

void object::light_in_loop(glm::vec3 lightobjectcolor, glm::mat4 view, glm::mat4 projection, glm::vec3 lightpos)
{
	useshader();
	setvec3("color", lightobjectcolor);
	setmat4("view", view);
	setmat4("projection", projection);


	//std::cout << axis.x<<"," << axis.y<<","<< axis.z << std::endl;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightpos);
	//model = glm::rotate(model, 4*sin(float(glfwGetTime())),axis);
	model = glm::scale(model, glm::vec3(lightscale));
	setmat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void object::collision(obj_info& obj_A, obj_info& obj_B, float scale,float deltatime)
{
	obj_A.velocity += obj_A.acceleration * deltatime;
	obj_B.velocity += obj_B.acceleration * deltatime;

	obj_A.position -= obj_A.velocity * deltatime;
	obj_B.position -= obj_B.velocity * deltatime;

	if (distance_calc(obj_A.position, obj_B.position) < scale)
	{
		glm::vec3 velocityA = obj_A.velocity;
		glm::vec3 velocityB = obj_B.velocity;

		obj_A.velocity = (velocityA + velocityB) * 0.75f;	
		obj_B.velocity = (velocityA + velocityB) * 0.75f;

		//std::cout << velocityA.x << velocityA.y << velocityA.z << std::endl;
		std::cout << obj_A.position.x << obj_A.position.y << obj_A.position.z << std::endl;

		float x = (obj_A.position.x - obj_B.position.x);
		float y = (obj_A.position.y - obj_B.position.y);
		float z = (obj_A.position.z - obj_B.position.z);

		obj_A.position.x += x;
		obj_B.position.x -= x;

		obj_A.position.y += y * deltatime;
		obj_B.position.y -= y * deltatime;

		obj_A.position.z += z*0.005;
		obj_B.position.z -= z*0.005;



		//std::cout << distance_calc(obj_A.position, obj_B.position) << std::endl;
	}
}

float object::distance_calc(glm::vec3 posa, glm::vec3 posb)
{
	return glm::sqrt(glm::pow((posa.x - posb.x), 2) + glm::pow((posa.y - posb.y), 2) + glm::pow((posa.z - posb.z), 2));
}