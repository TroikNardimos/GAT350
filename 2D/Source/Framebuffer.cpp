#include "Framebuffer.h"
#include "Renderer.h"

Framebuffer::Framebuffer(const Renderer& renderer, int width, int height)
{
	m_width = width;
	m_height = height;
	m_pitch = width * sizeof(colour_t);

	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!m_texture)
	{
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
	}
	m_buffer.resize(m_width * m_height);
}

Framebuffer::~Framebuffer()
{
	SDL_DestroyTexture(m_texture);
}

void Framebuffer::Update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), m_pitch);
}

void Framebuffer::Clear(const colour_t& color)
{
	std::fill(m_buffer.begin(), m_buffer.end(), color);
}

void Framebuffer::DrawPoint(int x, int y, const colour_t& color)
{
	if (x >= m_width || x < 0 || y >= m_height || y < 0) return;
	m_buffer[x + (y * m_width)] = color;
}

void Framebuffer::DrawRect(int x, int y, int w, int h, const colour_t& colour)
{
	if (x >= m_width || x + w < 0 || y >= m_height || y + h < 0) return;

	int x1 = std::max(x,0);
	int x2 = std::min(x+w, m_width);
	int y1 = std::max(y,0);
	int y2 = std::min(y+h, m_height);

	for (int sy = y1; sy < y2; sy++)
	{
		int index = x1 + sy * m_width;
		std::fill(m_buffer.begin() + index, m_buffer.begin() + (index + x2 - x1), colour);
		//for (int sx = x1; sx < x2; sx++)
		{
			//m_buffer[index++] = colour;
		}
	}
}

void Framebuffer::DrawLineSlope(int x1, int y1, int x2, int y2, const colour_t& colour)
{
	int dx = x2 - x1; //run
	int dy = y2 - y1; //rise

	if (dx == 0)
	{
		if (y1 > y2) std::swap(y1, y2);
		for (int y = y1; y < y2; y++)
		{
			m_buffer[x1 + y * m_width] = colour;
		}
	}
	else
	{
		//y=mx+b
		//m = rise / run
		float m = (float)dy / (float)dx;
		float b = y1 - (m * x1);

		if (std::abs(dx) > std::abs(dy))
		{
			for (int x = x1; x < x2; x++)
			{
				int y = (int)round(m * x) + b;
				m_buffer[x + y * m_width] = colour;
			}
		}
		else
		{
			for (int y = y1; y < y2; y++)
			{
				//int y = (int)round(m * x) + b;
				int x = (int)round(y - b) / m;
				m_buffer[x + y * m_width] = colour;
			}
		}
	}
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const colour_t& colour)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	bool steep = (std::abs(dy) > std::abs(dx));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	dx = x2 - x1;
	dy = std::abs(y2 - y1);

	int error = dx / 2;
	int ystep = (y1 < y2) ? 1 : -1;
	
	for (int x = x1, y = y1; x <= x2; x++)
	{
		(steep) ? DrawPoint(y, x, colour) : DrawPoint(x, y, colour);
		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void Framebuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const colour_t& colour)
{
	DrawLine(x1,y1,x2,y2, colour);
	DrawLine(x2,y2,x3,y3, colour);
	DrawLine(x3,y3,x1,y1, colour);
}

void Framebuffer::DrawCircle(int xc, int yc, int r, const colour_t& colour)
{
	int x = 0;
	int y = r;
	int d = 3 - 2 * r;
	DrawCircleSegment(xc, yc, x, y, colour);
	while (y >= x)
	{
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
		{
			d = d + 4 * x + 6;
		}
		x++;
		DrawCircleSegment(xc, yc, x, y, colour);
	}
}

void Framebuffer::DrawCircleSegment(int xc, int yc, int x, int y, const colour_t& colour)
{
	DrawPoint(xc + x, yc + y, colour);
	DrawPoint(xc - x, yc + y, colour);
	DrawPoint(xc + x, yc - y, colour);
	DrawPoint(xc - x, yc - y, colour);
	DrawPoint(xc + y, yc + x, colour);
	DrawPoint(xc - y, yc + x, colour);
	DrawPoint(xc + y, yc - x, colour);
	DrawPoint(xc - y, yc - x, colour);
}