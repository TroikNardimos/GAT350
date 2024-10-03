#pragma once
#include <SDL.h>
#include <iostream>
#include <string>

class Renderer
{
public:
	Renderer() = default;
	~Renderer();

	int Initialize();
	void Shutdown();

	int CreateWindow(std::string title, int width, int height);
	void BeginFrame();
	void EndFrame();
	void CopyFramebuffer(const class Framebuffer& framebuffer);

	void operator = (const class Framebuffer& framebuffer);

public:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };

	int m_width{ 0 };
	int m_height{ 0 };
};