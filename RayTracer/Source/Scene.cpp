#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Tracer.h"
#include "Random.h"
#include <iostream>
#include "ETime.h"

void Scene::Update()
{
	for (auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples, int depth)
{
	Time frameTimer;
	Time scanlineTimer;
	for (int y = 0; y < framebuffer.m_height; y++)
	{
		scanlineTimer.Reset();
		for (int x = 0; x < framebuffer.m_width; x++)
		{
			colour3_t colour{0};
			for (int i = 0; i < numSamples; i++)
			{
				glm::vec2 pixel{x, y};
				pixel += glm::vec2{randomf(0,1), randomf(0,1)};
				glm::vec2 point = pixel / glm::vec2{framebuffer.m_width, framebuffer.m_height};
				point.y = 1 - point.y;

				ray_t ray = camera.GetRay(point);

				colour += Tracer::Trace(*this, ray, 0.001f, 100.0f, depth);
			}
			colour.r = (float)(colour.r / numSamples);
			colour.g = (float)(colour.g / numSamples);
			colour.b = (float)(colour.b / numSamples);
			framebuffer.DrawPoint(x, y, ColourConvert(colour));
		}
		std::cout << "y: " << y << " - " << scanlineTimer.GetElapsedTime() << std::endl;
	}
	std::cout << "frame time: " << frameTimer.GetElapsedTime() << std::endl;
}
