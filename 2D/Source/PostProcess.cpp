#include "PostProcess.h"
#include "MathUtils.h"
#include <algorithm>
#include <cmath>

namespace PostProcess
{
	void PostProcess::Invert(std::vector<colour_t>& buffer)
	{
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
	void ColourBalance(std::vector<colour_t>& buffer, int ro, int go, int bo)
	{
		std::for_each(buffer.begin(), buffer.end(), [ro, go, bo](auto& c)
			{
				c.r = static_cast<uint8_t>(Clamp(c.r + ro, 0, 255));
				c.g = static_cast<uint8_t>(Clamp(c.g + go, 0, 255));
				c.b = static_cast<uint8_t>(Clamp(c.b + bo, 0, 255));
			});
	}
	void Brightness(std::vector<colour_t>& buffer, int brightness)
	{
		std::for_each(buffer.begin(), buffer.end(), [brightness](auto& c)
			{
				c.r = static_cast<uint8_t>(Clamp(c.r + brightness, 0, 255));
				c.g = static_cast<uint8_t>(Clamp(c.g + brightness, 0, 255));
				c.b = static_cast<uint8_t>(Clamp(c.b + brightness, 0, 255));
			});
	}
	void Noise(std::vector<colour_t>& buffer, uint8_t noise)
	{
		std::for_each(buffer.begin(), buffer.end(), [noise](auto& c)
			{
				int offset = (rand() % ((noise << 1) + 1)) - noise;
				c.r = static_cast<uint8_t>(Clamp(c.r + offset, 0, 255));
				c.g = static_cast<uint8_t>(Clamp(c.r + offset, 0, 255));
				c.b = static_cast<uint8_t>(Clamp(c.r + offset, 0, 255));
			});
	}
	void Threshhold(std::vector<colour_t>& buffer, uint8_t threshold)
	{
		std::for_each(buffer.begin(), buffer.end(), [threshold](auto& c)
			{
				int value = (int)((c.r + c.g + c.b) / 3);

				c.r = (value >= threshold) ? 255 : 0;
				c.g = (value >= threshold) ? 255 : 0;;
				c.b = (value >= threshold) ? 255 : 0;;
			});
	}
	void Posterize(std::vector<colour_t>& buffer, uint8_t levels)
	{
		uint8_t level = static_cast<uint8_t>(255 / levels);
		std::for_each(buffer.begin(), buffer.end(), [level](auto& c)
			{
				c.r = (c.r / level) * level;
				c.g = (c.g / level) * level;
				c.b = (c.b / level) * level;
			});
	}
	void BoxBlur(std::vector<colour_t>& buffer, int width, int height)
	{
		std::vector<colour_t> source = buffer;

		int k[3][3] =
		{
			{1,1,1},
			{1,1,1},
			{1,1,1}
		};

		for (int i = 0; i < buffer.size(); i++)
		{
			// % 5 : 1 2 3 4 5 6 7 8 9 10
			//       1 2 3 4 0 1 2 3 4 0
			int x = i % width;
			int y = i / width;

			//skip if out of bounds
			if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

			int r = 0;
			int g = 0;
			int b = 0;

			for (int iy = 0; iy < 3; iy++)
			{
				for (int ix = 0; ix < 3; ix++)
				{
					colour_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
					int weight = k[iy][ix];

					r += pixel.r * weight;
					g += pixel.g * weight;
					b += pixel.b * weight;
				}
			}
			colour_t& colour = buffer[i];
			colour.r = static_cast<uint8_t>(r / 9);
			colour.g = static_cast<uint8_t>(g / 9);
			colour.b = static_cast<uint8_t>(b / 9);
		}
	}
	void GaussianBlur(std::vector<colour_t>& buffer, int width, int height)
	{
		std::vector<colour_t> source = buffer;

		int k[3][3] =
		{
			{1,2,1},
			{2,4,2},
			{1,2,1}
		};

		for (int i = 0; i < buffer.size(); i++)
		{
			// % 5 : 1 2 3 4 5 6 7 8 9 10
			//       1 2 3 4 0 1 2 3 4 0
			int x = i % width;
			int y = i / width;

			//skip if out of bounds
			if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

			int r = 0;
			int g = 0;
			int b = 0;

			for (int iy = 0; iy < 3; iy++)
			{
				for (int ix = 0; ix < 3; ix++)
				{
					colour_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
					int weight = k[iy][ix];

					r += pixel.r * weight;
					g += pixel.g * weight;
					b += pixel.b * weight;
				}
			}
			colour_t& colour = buffer[i];
			colour.r = static_cast<uint8_t>(r / 16);
			colour.g = static_cast<uint8_t>(g / 16);
			colour.b = static_cast<uint8_t>(b / 16);
		}
	}
	void Sharpen(std::vector<colour_t>& buffer, int width, int height)
	{
		std::vector<colour_t> source = buffer;

		int k[3][3] =
		{
			{0,-1,0},
			{-1,5,-1},
			{0,-1,0}
		};

		for (int i = 0; i < buffer.size(); i++)
		{
			// % 5 : 1 2 3 4 5 6 7 8 9 10
			//       1 2 3 4 0 1 2 3 4 0
			int x = i % width;
			int y = i / width;

			//skip if out of bounds
			if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

			int r = 0;
			int g = 0;
			int b = 0;

			for (int iy = 0; iy < 3; iy++)
			{
				for (int ix = 0; ix < 3; ix++)
				{
					colour_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
					int weight = k[iy][ix];

					r += pixel.r * weight;
					g += pixel.g * weight;
					b += pixel.b * weight;
				}
			}
			colour_t& colour = buffer[i];
			colour.r = static_cast<uint8_t>(Clamp(r, 0, 255));
			colour.g = static_cast<uint8_t>(Clamp(g, 0, 255));
			colour.b = static_cast<uint8_t>(Clamp(b, 0, 255));
		}
	}
	void Edge(std::vector<colour_t>& buffer, int width, int height, int threshold)
	{
		std::vector<colour_t> source = buffer;

		int hk[3][3] =
		{
			{1,0,-1},
			{2,0,-2},
			{1,0,-1}
		};

		int vk[3][3] =
		{
			{-1,-2,-1},
			{0,0,0},
			{1,2,1}
		};

		for (int i = 0; i < buffer.size(); i++)
		{
			// % 5 : 1 2 3 4 5 6 7 8 9 10
			//       1 2 3 4 0 1 2 3 4 0
			int x = i % width;
			int y = i / width;

			//skip if out of bounds
			if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

			int h = 0;
			int v = 0;

			for (int iy = 0; iy < 3; iy++)
			{
				for (int ix = 0; ix < 3; ix++)
				{
					colour_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];

					h += pixel.r * hk[iy][ix];
					v += pixel.r * vk[iy][ix];
				}
			}
			int m = std::sqrt(h * h + v * v);
			m = (m > threshold) ? m : 0;
			uint8_t c = std::clamp(m, 0, 255);

			colour_t& colour = buffer[i];
			colour.r = c;
			colour.g = c;
			colour.b = c;
		}
	}
	void Emboss(std::vector<colour_t>& buffer, int width, int height)
	{
		// create source buffer to read from, buffer will be written to
		std::vector<colour_t> source = buffer;

		// kernal values
		int16_t k[3][3] =
		{
			{-2,-1,0},
			{-1,0,1},
			{0,1,2}
		};

		// process buffer pixels
		for (int i = 0; i < buffer.size(); i++)
		{
			// get pixel x, y
			int x = i % width;
			int y = i / width;

			// check bounds (x and y must be one pixel away from buffer edges)
			if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

			// color values from kernel operation
			int r = 0;
			int g = 0;
			int b = 0;

			// process kernel pixels
			for (int iy = 0; iy < 3; iy++)
			{
				for (int ix = 0; ix < 3; ix++)
				{
					// get pixel in kernel
					const colour_t& pixel = source[(x + ix - 1) + (y + iy - 1) * width];
					// get kernel weight
					int weight = k[iy][ix];

					// accumulate color values of kernel pixels
					r += pixel.r * weight;
					g += pixel.g * weight;
					b += pixel.b * weight;
				}
			}

			// set buffer color, set values from average of kernel color values
			colour_t& colour = buffer[i];
			// help from ChatGPT
			colour.r = static_cast<uint8_t>(Clamp(r + 128, 0, 255));
			colour.g = static_cast<uint8_t>(Clamp(g + 128, 0, 255));
			colour.b = static_cast<uint8_t>(Clamp(b + 128, 0, 255));
		}
	}
}
