#include "Tracer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"

colour3_t Tracer::Trace(Scene& scene, const ray_t& ray)
{
	// check for object hit in scene
	for (auto& object : scene.m_objects)
	{
		if (object->Hit(ray))
		{
			return { 1,0,0 };
		}
	}


	//sky
	colour3_t colour{ 0 };
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f;
	colour = Lerp(colour3_t{ 1, 1, 1 }, colour3_t{ 0.5f, 0.7f, 1.0f }, t);

	return colour;
}