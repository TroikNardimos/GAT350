#pragma once
#include "Colour.h"
#include "VertexShader.h"

#include <glm\glm.hpp>
#include <vector>
#include <string>

//using vertex_t = glm::vec3;
//using vertices_t = std::vector<vertex_t>;

class Model
{
public:
	Model() = default;
	Model(const vertexbuffer_t& vertices, const colour4_t& colour) : m_vb{ vertices }, m_colour{colour} {}

	void Draw();
	bool Load(const std::string& filename);
	void SetColour(const colour4_t& colour) { m_colour = colour; }

private:
	vertexbuffer_t m_vb;
	colour4_t m_colour{1};
};