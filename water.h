#pragma once
#include "object.h"
class water : public object
{
public:
    unsigned int VAO = 2, EBO = 0;
    //unsigned int shaderprgm;
   
    water(const char* vertex, const char* fragment) : object(vertex, fragment) {};

    void set_watercoors(float grid_size = 500.0f);

    void set_visual(water& water, glm::mat4 view, glm::mat4 projection, glm::vec3 lightobjectcolor, glm::vec3 lightpos, glm::vec3 camerapos, glm::mat4 sh_projection, unsigned int waterVAO);

    void set_water_objects(unsigned int& waterVBO);

protected:
    std::vector <unsigned int> water_index;
    std::vector <float> water_vertices; std::vector <unsigned int> water_indices;
    unsigned int set_shader(const char* vertexpath, const char* fragmentpath);


};

