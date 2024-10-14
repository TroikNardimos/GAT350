#include "Colour.h"

colour_t(*blend_func)(const colour_t& src, const colour_t& dst);

void SetBlendMode(BlendMode blendMode)
{
	switch (blendMode)
	{
	case BlendMode::Normal:
		blend_func = NormalBlend;
		break;
	case BlendMode::Alpha:
		blend_func = AlphaBlend;
		break;
	case BlendMode::Additive:
		blend_func = AdditiveBlend;
		break;
	case BlendMode::Multiply:
		//blend_func = MultiplyBlend;
		break;
	default:
		break;
	}
}

colour_t ColourBlend(const colour_t& src, const colour_t& dst)
{
	return blend_func(src, dst);
}

colour_t NormalBlend(const colour_t& src, const colour_t& dst)
{

	return src;
}

colour_t AlphaBlend(const colour_t& src, const colour_t& dst)
{
	uint8_t alpha = src.a;
	uint8_t inv_alpha = 255 - src.a;

	colour_t colour;
	colour.r = (src.r * alpha + dst.r * inv_alpha) >> 8;
	colour.g = (src.g * alpha + dst.g * inv_alpha) >> 8;
	colour.b = (src.b * alpha + dst.b * inv_alpha) >> 8;
	colour.a = src.a;

	return colour;
}

colour_t AdditiveBlend(const colour_t& src, const colour_t& dst)
{
	colour_t colour;
	colour.r = std::min(src.r + dst.r, 255);
	colour.g = std::min(src.g + dst.g, 255);
	colour.b = std::min(src.b + dst.b, 255);
	colour.a = src.a;

	return colour;
}