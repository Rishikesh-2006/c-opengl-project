#include "object.h"

void Set_Object(float vertices[],int num_items,int stride, const std::array<int, 2>& tex = {0 , 0}/* tex position 1 is the location
	of the first instance of the texture and 2 is the number of elements of texture per vertex */, unsigned int indices[])
{
	GLuint CUBEVAO;
	GLuint CUBEEBO;

	glGenVertexArrays(1, &CUBEVAO);
	glGenBuffers(1, &OGVBO);

	glBindVertexArray(CUBEVAO);

	glBindBuffer(GL_ARRAY_BUFFER, OGVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &CUBEEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CUBEEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	int update = 0;
	/*glVertexAttribPointer(1, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, 0, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
	*/
	bool texture = true;

	if (tex[0] == tex[1] == 0)
	{
		texture = false;
	}

	for (int i = 0; i < num_items;i++)
	{
		glVertexAttribPointer(i, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(update * sizeof(float)));
		glEnableVertexAttribArray(i);


		if (texture && i == tex[0])
		{
			glVertexAttribPointer(i, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)((update+tex[1]) * sizeof(float)));
			glEnableVertexAttribArray(i);
		}

		update += stride;
	}
}

void Set_Object_AVBO(float vertices[], int num_items, unsigned int indices[], const std::array <int, 2>& tex = { 0,0 },int stride, unsigned int VBO)
{

	GLuint VAO;
	GLuint EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	bool texture = true;
	int update = 0;

	if (tex[0] == tex[1] == 0)
	{
		texture = false;
	}

	for (int i = 0; i < num_items;i++)
	{
		glVertexAttribPointer(i, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(update * sizeof(float)));
		glEnableVertexAttribArray(i);

		if (texture && i == tex[1])
		{
			glVertexAttribPointer(i, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)((update + tex[2]) * sizeof(float)));
			glEnableVertexAttribArray(i);
		}

		update += stride;

	}

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}