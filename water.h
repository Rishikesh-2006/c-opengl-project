#pragma once
#include "object.h"
class water : public object
{
public:
    unsigned int VAO = 2, EBO = 0;
    unsigned int framebufferid, textureid, depthid;
    std::vector <float> water_vertices; std::vector <unsigned int> water_indices;
    int scheight;
    int scwidth;
    //unsigned int shaderprgm;

    water(const char* vertex, const char* fragment) : object(vertex, fragment) {};

    void set_resolution(int width, int height);
    void set_watercoors(float grid_size = 500.0f);

    void set_visual(water& water, glm::mat4 view, glm::mat4 projection, glm::vec3 lightobjectcolor, glm::vec3 lightpos, glm::vec3 camerapos, glm::mat4 sh_projection, unsigned int waterVAO,unsigned int fbo);

    void set_water_objects(unsigned int& waterVBO);

    //reflections

    unsigned int framebuffer();
    unsigned int framebuffertexture(int width, int height);
    unsigned int depthTEXTURE(int width, int height);
    unsigned int renderbuffer(int width, int height);
    void bindframebuffer(unsigned int framebuffer, int width, int height);
    void UNbindframebuffer(int width, int height);
    void setfbo();
    void bindfbo();
    void cleanbuffers();

protected:
    int reflection_width = 320;
    int reflection_height = 180;

    unsigned int set_shader(const char* vertexpath, const char* fragmentpath);


};

