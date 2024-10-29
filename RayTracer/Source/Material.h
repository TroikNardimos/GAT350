#pragma once
#include "Colour.h"
#include "Ray.h"

class Material
{
public:
	Material() = default;
	Material(const colour3_t& colour) : m_albedo{colour}{}

	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, colour3_t& attenuation, ray_t& scatter) = 0;

	colour3_t& GetColour() { return m_albedo; }

protected:
	colour3_t m_albedo;

};

class Lambertian : public Material
{
public:
	Lambertian(const colour3_t& albedo) : Material{ albedo } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, colour3_t& attenuation, ray_t& scatter);

};