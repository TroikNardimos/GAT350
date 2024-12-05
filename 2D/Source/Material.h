#pragma once
#include "Colour.h"
#include <glm/glm.hpp>

struct material_t
{
	colour3_t albedo{ 1 };
	colour3_t specular{ 1 };
	float shininess{ 1 };
};