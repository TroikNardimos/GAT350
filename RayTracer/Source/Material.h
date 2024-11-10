#pragma once
#include "Colour.h"
#include "Ray.h"

class Material
{
public:
	//Material() = default;
	Material(const colour3_t& colour) : m_albedo{colour}{}

	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, colour3_t& attenuation, ray_t& scatter) const = 0;

	colour3_t& GetColour() { return m_albedo; }
	virtual colour3_t GetEmissive() const { return colour3_t{ 0 }; }

protected:
	colour3_t m_albedo{0};

};

class Lambertian : public Material
{
public:
	Lambertian(const colour3_t& albedo) : Material{ albedo } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, colour3_t& attenuation, ray_t& scatter) const override;

};

class Metal : public Material
{
public:
	Metal(const colour3_t& albedo, float fuzz) : Material{ albedo }, m_fuzz{ fuzz } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, colour3_t& attenuation, ray_t& scatter) const override;

protected:
	float m_fuzz = 0;

};

class Dielectric : public Material
{
public:
	Dielectric(const colour3_t& albedo, float refractiveIndex) : Material{ albedo }, m_refractiveIndex{ refractiveIndex } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, colour3_t& attenuation, ray_t& scatter) const override;

protected:
	float m_refractiveIndex = 0;

};

class Emissive : public Material
{
public:
	Emissive(const colour3_t& albedo, float intensity = 1) : Material{ albedo }, m_intensity{ intensity } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, colour3_t& attenuation, ray_t& scatter) const override { return false; }
	colour3_t GetEmissive() const override { return m_albedo * m_intensity; }

private:
	float m_intensity {1};

};

