#pragma once
#include "MathUtils.h"
#include <SDL.h>
#include <algorithm>
#include <glm/glm.hpp>

using colour_t = SDL_Color;
using colour3_t = glm::vec3;
using colour4_t = glm::vec4;

inline colour_t ColourConvert(const glm::vec4& colour4)
{
	colour_t colour;

	colour.r = (uint8_t)(Clamp(colour4.r * 255, 0.0f, 255.0f));
	colour.g = (uint8_t)(Clamp(colour4.g * 255, 0.0f, 255.0f));
	colour.b = (uint8_t)(Clamp(colour4.b * 255, 0.0f, 255.0f));
	colour.a = (uint8_t)(Clamp(colour4.a * 255, 0.0f, 255.0f));

	return colour;
}


inline colour_t ColourConvert(const glm::vec3& colour3)
{
	colour_t colour;

	colour.r = (uint8_t)(Clamp(colour3.r * 255, 0.0f, 255.0f));
	colour.g = (uint8_t)(Clamp(colour3.g * 255, 0.0f, 255.0f));
	colour.b = (uint8_t)(Clamp(colour3.b * 255, 0.0f, 255.0f));
	colour.a = 255;

	return colour;
}


inline colour4_t colourConvert(const colour_t& colour)
{
	colour4_t colour4;

	colour4.r = colour.r / 255.0f;
	colour4.g = colour.g / 255.0f;
	colour4.b = colour.b / 255.0f;
	colour4.a = colour.a / 255.0f;

	return colour4;
}

// colour blending
enum class BlendMode
{
	Normal,
	Alpha,
	Additive,
	Multiply
};

void SetBlendMode(BlendMode blendMode);
colour_t ColourBlend(const colour_t& src, const colour_t& dst);

colour_t NormalBlend(const colour_t& src, const colour_t& dst);
colour_t AlphaBlend(const colour_t& src, const colour_t& dst);
colour_t AdditiveBlend(const colour_t& src, const colour_t& dst);
colour_t MultiplyBlend(const colour_t& src, const colour_t& dst);