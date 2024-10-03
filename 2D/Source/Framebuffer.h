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
	void DrawRect(int x, int y, int w, int h, colour_t colour);

public:
	int m_width{ 0 };
	int m_height{ 0 };
	int m_pitch{ 0 };

	SDL_Texture* m_texture{ nullptr };
	std::vector<colour_t> m_buffer;
};