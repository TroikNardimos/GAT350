#pragma once
#include "Colour.h"
#include "Ray.h"

class Tracer
{
public:
	static colour3_t Trace(class Scene& scene, const ray_t& ray);
};