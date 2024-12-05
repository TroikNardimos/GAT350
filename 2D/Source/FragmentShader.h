#pragma once
#include "Colour.h"

struct fragment_input_t
{
	glm::vec3 position;
	glm::vec3 normal;
	colour4_t colour;
};

class FragmentShader
{
public:
	static colour4_t Process(const fragment_input_t& fragment);
};