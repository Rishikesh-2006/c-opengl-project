#pragma once
#include "object.h"
class water : public object
{
public:
    unsigned int VAO, EBO = 0;
    water(const char* vertex, const char* fragment) : object(vertex, fragment) {};

    void set_watercoors(float grid_size = 500.0f);

    void set_visual(glm::mat4 view, glm::mat4 projection, glm::vec3 lightobjectcolor, glm::vec3 lightpos, glm::vec3 camerapos, glm::mat4 sh_projection);

    void set_water_objects(unsigned int& waterVBO, std::vector <unsigned int> water_indices, std::vector <float> water_vertices);
private:
    std::vector <unsigned int> water_index;

};

