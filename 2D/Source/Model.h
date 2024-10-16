#pragma once
#include "Colour.h"

#include <glm\glm.hpp>
#include <vector>

using vertex_t = glm::vec3;
using vertices_t = std::vector<vertex_t>;

class Model
{
public:
	Model() = default;
	Model(const vertices_t& vertices, const colour_t& colour) : m_vertices{ vertices }, m_colour{colour} {}

	void Draw(class Framebuffer& framebuffer, const glm::mat4& model);

private:
	vertices_t m_vertices;
	colour_t m_colour;
};