#pragma once
#include "Framebuffer.h"

namespace PostProcess
{
	void Invert(std::vector<colour_t>& buffer);
	void Monochrome(std::vector<colour_t>& buffer);
	void ColourBalance(std::vector<colour_t>& buffer);
	void BrightnessAdjustment(std::vector<colour_t>& buffer, int brightness);
	void NoiseEffect(std::vector<colour_t>& buffer);
	void Threshholding(std::vector<colour_t>& buffer);
}