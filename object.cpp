#include "object.h"

void object::collision(float deltatime, float wall,glm::vec3 position, glm::vec3 rotation)
{
	velocity += acceleration * deltatime;

	position.x -= velocity.x * deltatime;
	position.y -= velocity.y * deltatime;

	rotation -= 0.3f*velocity.x*velocity.y;
}