#pragma once
#include "object.h"

class water : public object
{
public:
    unsigned int framebufferid = 0, textureid = 0 , depthid = 0;
    
    int scheight;
    int scwidth;
    //unsigned int shaderprgm;

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


protected:

    unsigned int set_shader(const char* vertexpath, const char* fragmentpath);

private:
    unsigned int reflectionFrameBuffer;
    unsigned int reflectionTexture;
    unsigned int reflectionDepthBuffer;

    unsigned int refractionFrameBuffer;
    unsigned int refractionTexture;
    unsigned int refractionDepthTexture;

    int REFLECTION_WIDTH = 320;
    int REFLECTION_HEIGHT = 180;

    int REFRACTION_WIDTH = 1280;
    int REFRACTION_HEIGHT = 720;

    int width;
    int height;

    std::vector <float> water_vertices; std::vector <unsigned int> water_indices;
};

