#pragma once
#include "Model.h"
#include "Transform.h"
#include <memory>
#include "Material.h"

class Actor
{
public:
	Actor(const Transform& transform, std::shared_ptr<Model> model, std::shared_ptr<material_t> material) : 
		m_transform{ transform }, 
		m_model{ model },
		m_material{material} 
	{}

	Transform& GetTransfrom() { return m_transform; }
	const Transform& GetTransfrom() const { return m_transform; }

	void Draw();
private:
	Transform m_transform;
	std::shared_ptr<Model> m_model;
	std::shared_ptr<material_t> m_material;
};