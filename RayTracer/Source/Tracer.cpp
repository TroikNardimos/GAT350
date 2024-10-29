#include "Tracer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"

colour3_t Tracer::Trace(Scene& scene, const ray_t& ray, float minDistance, float maxDistance)
{
	raycastHit_t raycastHit;
	float closestDistance = maxDistance;
	bool isHit = false;

	// check for object hit in scene
	for (auto& object : scene.m_objects)
	{
		if (object->Hit(ray, raycastHit, minDistance, closestDistance))
		{
			isHit = true;
			closestDistance = raycastHit.distance;
			//return object->GetMaterial().lock()->GetColour();
		}
	}

	if (isHit)
	{
		colour3_t attenuation;
		ray_t scatter;
		if (raycastHit.material.lock()->Scatter(ray, raycastHit, attenuation, scatter))
		{
			return attenuation * Trace(scene, scatter, minDistance, maxDistance);
		}
		//return raycastHit.material.lock()->GetColour();
	}

	//sky
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f;
	colour3_t colour = Lerp(colour3_t{ 1, 1, 1 }, colour3_t{ 0.5f, 0.7f, 1.0f }, t);

	return colour;
}
