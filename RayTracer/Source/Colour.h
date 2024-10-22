#pragma once
#include <SDL.h>
#include <algorithm>

using colour_t = SDL_Color;

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