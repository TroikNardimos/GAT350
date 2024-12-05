#pragma once
#include "Colour.h"
#include "Light.h"
#include <array>

struct vertex_t
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

using vertexbuffer_t = std::vector<vertex_t>;

struct vertex_output_t
{
	glm::vec4 position;
	glm::vec4 vposition;
	glm::vec3 normal;
	colour3_t colour;
};

class VertexShader
{
public:
	static void Process(const vertex_t& ivertex, vertex_output_t& overtex);

public:

};


