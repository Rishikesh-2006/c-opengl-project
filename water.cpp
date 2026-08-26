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
}

std::vector <float> water::get_vertex_data()
{
    return water_vertices;
}

std::vector <unsigned int> water::get_index_data()
{
    return water_indices;
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

void water::setvertexdata(std::vector<float> vertex, std::vector<unsigned int> index,int width , int height)
{
	this->water_vertices = vertex;
	this->water_indices = index;
    this->width = width;
    this->height = height;
}



//FRAMEBUFFER

void water::WaterFrameBuffers()
{
    // Call when loading the game
    initialiseReflectionFrameBuffer();
    initialiseRefractionFrameBuffer();
}

void water::cleanUp()
{
    // Call when closing the game
    glDeleteFramebuffers(1, &reflectionFrameBuffer);
    glDeleteTextures(1, &reflectionTexture);
    glDeleteRenderbuffers(1, &reflectionDepthBuffer);

    glDeleteFramebuffers(1, &refractionFrameBuffer);
    glDeleteTextures(1, &refractionTexture);
    glDeleteTextures(1, &refractionDepthTexture);
}

void water::bindReflectionFrameBuffer()
{
    // Call before rendering to this FBO
    bindFrameBuffer(
        reflectionFrameBuffer,
        REFLECTION_WIDTH,
        REFLECTION_HEIGHT
    );
}

void water::bindRefractionFrameBuffer()
{
    // Call before rendering to this FBO
    bindFrameBuffer(
        refractionFrameBuffer,
        REFRACTION_WIDTH,
        REFRACTION_HEIGHT
    );
}

void water::unbindCurrentFrameBuffer()
{
    // Switch back to default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(
        0,
        0,
        width,
        height
    );
}

GLuint water::getReflectionTexture()
{
    return reflectionTexture;
}

GLuint water::getRefractionTexture()
{
    return refractionTexture;
}

GLuint water::getRefractionDepthTexture()
{
    return refractionDepthTexture;
}


void water::initialiseReflectionFrameBuffer()
{
    reflectionFrameBuffer = createFrameBuffer();

    reflectionTexture =
        createTextureAttachment(
            REFLECTION_WIDTH,
            REFLECTION_HEIGHT
        );

    reflectionDepthBuffer =
        createDepthBufferAttachment(
            REFLECTION_WIDTH,
            REFLECTION_HEIGHT
        );

    unbindCurrentFrameBuffer();
}


void water::initialiseRefractionFrameBuffer()
{
    refractionFrameBuffer = createFrameBuffer();

    refractionTexture =
        createTextureAttachment(
            REFRACTION_WIDTH,
            REFRACTION_HEIGHT
        );

    refractionDepthTexture =
        createDepthTextureAttachment(
            REFRACTION_WIDTH,
            REFRACTION_HEIGHT
        );

    unbindCurrentFrameBuffer();
}


void water::bindFrameBuffer(
    GLuint frameBuffer,
    int width,
    int height
)
{
    // Make sure no texture is bound
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glViewport(
        0,
        0,
        width,
        height
    );
}


GLuint water::createFrameBuffer()
{
    GLuint frameBuffer;

    // Generate framebuffer
    glGenFramebuffers(1, &frameBuffer);

    // Bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    // Render to color attachment 0
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    return frameBuffer;
}


GLuint water::createTextureAttachment(
    int width,
    int height
)
{
    GLuint texture;

    // Generate texture
    glGenTextures(1, &texture);

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // Allocate texture storage
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    // Filtering
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );

    // Attach texture to framebuffer
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        texture,
        0
    );

    return texture;
}


GLuint water::createDepthTextureAttachment(int width,int height)
{
    GLuint texture;

    // Generate texture
    glGenTextures(1, &texture);

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // Allocate depth texture
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_DEPTH_COMPONENT32,
        width,
        height,
        0,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        nullptr
    );

    // Filtering
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );

    // Attach depth texture
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        texture,
        0
    );

    return texture;
}


GLuint water::createDepthBufferAttachment(
    int width,
    int height
)
{
    GLuint depthBuffer;

    // Generate renderbuffer
    glGenRenderbuffers(1, &depthBuffer);

    // Bind renderbuffer
    glBindRenderbuffer(
        GL_RENDERBUFFER,
        depthBuffer
    );

    // Allocate depth storage
    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT,
        width,
        height
    );

    // Attach depth renderbuffer
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_RENDERBUFFER,
        depthBuffer
    );

    return depthBuffer;
}