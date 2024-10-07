#pragma once
#include <SDL.h>
#include <vector>

using colour_t = SDL_Color;

class Framebuffer
{
public:
	Framebuffer(const class Renderer& renderer, int width, int height);
	~Framebuffer();

	void Update();
	void Clear(const colour_t& color);

	void DrawPoint(int x, int y, const colour_t& color);
	void DrawRect(int x, int y, int w, int h, const colour_t& colour);
	void DrawLineSlope(int x1, int y1, int x2, int y2, const colour_t& colour);
	void DrawLine(int x1, int y1, int x2, int y2, const colour_t& colour);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const colour_t& colour);
	void DrawCircle(int xc, int yc, int r, const colour_t& colour);

private:
	void DrawCircleSegment(int xc, int yc, int x, int y, const colour_t& colour);

public:
	int m_width{ 0 };
	int m_height{ 0 };
	int m_pitch{ 0 };

	SDL_Texture* m_texture{ nullptr };
	std::vector<colour_t> m_buffer;
};