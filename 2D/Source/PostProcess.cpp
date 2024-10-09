#include "PostProcess.h"
#include "MathUtils.h"
#include <algorithm>

namespace PostProcess
{
	void PostProcess::Invert(std::vector<colour_t>& buffer)
	{
		//for (auto& colour : buffer)
		//{
		//	colour.r = 255 - colour.r;
		//	colour.g = 255 - colour.g;
		//	colour.b = 255 - colour.b;
		//}

		std::for_each(buffer.begin(), buffer.end(), [](auto& c)
			{
				c.r = 255 - c.r;
				c.g = 255 - c.g;
				c.b = 255 - c.b;
			});
	}

	void PostProcess::Monochrome(std::vector<colour_t>& buffer)
	{
		std::for_each(buffer.begin(), buffer.end(), [](auto& c)
			{
				int average = (int)((c.r + c.g + c.b) / 3);

				c.r = average;
				c.g = average;
				c.b = average;
			});
	}
	void BrightnessAdjustment(std::vector<colour_t>& buffer, int brightness)
	{
		std::for_each(buffer.begin(), buffer.end(), [brightness](auto& c)
			{
				c.r = static_cast<uint8_t>(Clamp(c.r + brightness, 0, 255));
				c.g = static_cast<uint8_t>(Clamp(c.g + brightness, 0, 255));
				c.b = static_cast<uint8_t>(Clamp(c.b + brightness, 0, 255));
			});
	}
}
