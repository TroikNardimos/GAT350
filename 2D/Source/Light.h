#pragma once
#include <glm/glm.hpp>
#include "Colour.h"

struct light_t
{
	glm::vec3 position;
	glm::vec3 direction;
	colour3_t colour;
};