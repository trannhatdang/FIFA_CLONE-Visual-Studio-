#include "engine/Components/Component.h"

Component::Component(const std::string& name, GameObject* gameObject) : m_name(name), gameObject(gameObject)
{

}

Component::~Component()
{

}

std::string Component::GetName() const
{
	return m_name;
}
