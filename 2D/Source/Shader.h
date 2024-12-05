#pragma once
#include "VertexShader.h"
#include "FragmentShader.h"

class Shader
{
public:
	struct uniforms_t
	{
		//transformations (mvp)
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		//lights
		light_t light;
		colour3_t ambient;
	};
public:
	static void Draw(const vertexbuffer_t& vb);
	static bool ToScreen(const vertex_output_t& vertex, glm::vec2& screen);

public:
	static class Framebuffer* framebuffer;

	static uniforms_t uniforms;
};