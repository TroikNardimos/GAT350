#pragma once
#include "Colour.h"

class Material
{
public:
	Material() = default;
	Material(const colour3_t& colour) : m_colour{colour}{}

	colour3_t& GetColour() { return m_colour; }

private:
	colour3_t m_colour;

};