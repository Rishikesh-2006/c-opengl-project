#include "object.h"

void object::set_object(unsigned int &VBO, unsigned int* indices,int indices_size)
{


	glGenVertexArrays(1, &floorVAO);
	glBindVertexArray(floorVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

	this->floorVAO = floorVAO;
	this->floorEBO = floorEBO;

	std::cout << floorVAO << "," << floorEBO << ","<<VBO<<std::endl;
}