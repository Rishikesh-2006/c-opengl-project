#pragma once
#include "object.h"

class water : public object
{
public:

    unsigned int framebufferid = 0, textureid = 0 , depthid = 0;

    water(const char* vertex, const char* fragment) : object(vertex, fragment) {};

    void set_watercoors(float grid_size = 500.0f);

    void set_water_objects(unsigned int& waterVBO);

    void setvertexdata(std::vector<float> vertex, std::vector<unsigned int> index,int width , int height);

    //reflections
    void WaterFrameBuffers();

    void cleanUp();

    void bindReflectionFrameBuffer();

    void bindRefractionFrameBuffer();

    void unbindCurrentFrameBuffer();

    std::vector <float> get_vertex_data();

    std::vector <unsigned int> get_index_data();

    GLuint getReflectionTexture();

    GLuint getRefractionTexture();

    GLuint getRefractionDepthTexture();

    void initialiseReflectionFrameBuffer();

    void initialiseRefractionFrameBuffer();

    void bindFrameBuffer(GLuint frameBuffer,
        int width,
        int height);

    GLuint createFrameBuffer();

    GLuint createTextureAttachment(int width,
        int height);

    GLuint createDepthTextureAttachment(int width, int height);

    GLuint createDepthBufferAttachment(int width,
        int height);
    
    void set_water_renderer(glm::mat4 view, glm::mat4 projection, unsigned int VAO);

    void set_clipPlane(glm::vec4 plane);

protected:

    unsigned int set_shader(const char* vertexpath, const char* fragmentpath);

private:
    unsigned int reflectionFrameBuffer = createFrameBuffer();
    unsigned int reflectionTexture = 0;
    unsigned int reflectionDepthBuffer = 0;

    unsigned int refractionFrameBuffer = createFrameBuffer();
    unsigned int refractionTexture = 0;
    unsigned int refractionDepthTexture = 0;

    int REFLECTION_WIDTH = 320;
    int REFLECTION_HEIGHT = 180;

    int REFRACTION_WIDTH = 1280;
    int REFRACTION_HEIGHT = 720;


    int height = 1080;
    int width = 1920;

    std::vector <float> water_vertices; std::vector <unsigned int> water_indices;
};

