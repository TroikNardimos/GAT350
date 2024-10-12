#pragma once
#include "Framebuffer.h"

namespace PostProcess
{
	void Invert(std::vector<colour_t>& buffer);
	void Monochrome(std::vector<colour_t>& buffer);
	void ColourBalance(std::vector<colour_t>& buffer, int ro, int go, int bo);
	void Brightness(std::vector<colour_t>& buffer, int brightness);
	void Noise(std::vector<colour_t>& buffer, uint8_t noise);
	void Threshhold(std::vector<colour_t>& buffer, uint8_t threshold);
	void Posterize(std::vector<colour_t>& buffer, uint8_t levels);

	void BoxBlur(std::vector<colour_t>& buffer, int width, int height);
	void GaussianBlur(std::vector<colour_t>& buffer, int width, int height);
	void Sharpen(std::vector<colour_t>& buffer, int width, int height);
	void Edge(std::vector<colour_t>& buffer, int width, int height, int threshold);
}