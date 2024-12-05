#pragma once
#include <SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include "MathUtils.h"
#include <SDL.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/color_space.hpp>

using colour_t = SDL_Color;

using colour3_t = glm::vec3;
using colour4_t = glm::vec4;

inline colour3_t HSVToRGB(glm::vec3 hsv)
{
	return glm::rgbColor(hsv);
}

inline colour3_t HSVToRGB(float hue, float saturation, float value)
{
	return glm::rgbColor(glm::vec3{ hue, saturation, value });
}

inline float LinearToGamma(float linear)
{
	if (linear > 0)
	{
		return std::sqrt(linear);
	}
	return 0;
}

inline colour_t ColourConvert(const glm::vec4& colour4)
{
	colour_t colour;

	colour.r = (uint8_t)(Clamp(LinearToGamma(colour4.r) * 255, 0.0f, 255.0f));
	colour.g = (uint8_t)(Clamp(LinearToGamma(colour4.g) * 255, 0.0f, 255.0f));
	colour.b = (uint8_t)(Clamp(LinearToGamma(colour4.b) * 255, 0.0f, 255.0f));
	colour.a = (uint8_t)(Clamp(LinearToGamma(colour4.a) * 255, 0.0f, 255.0f));

	return colour;
}


inline colour_t ColourConvert(const glm::vec3& colour3)
{
	colour_t colour;

	colour.r = (uint8_t)(Clamp(LinearToGamma(colour3.r) * 255, 0.0f, 255.0f));
	colour.g = (uint8_t)(Clamp(LinearToGamma(colour3.g) * 255, 0.0f, 255.0f));
	colour.b = (uint8_t)(Clamp(LinearToGamma(colour3.b) * 255, 0.0f, 255.0f));
	colour.a = 255;

	return colour;
}

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