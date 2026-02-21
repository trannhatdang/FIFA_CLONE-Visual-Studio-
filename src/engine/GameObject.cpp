#include "engine/GameObject.h"
#include "engine/Components/Transform.h"

GameObject::GameObject(std::string name, std::string tag) : m_name(name), m_tag(tag)
{
	this->AddComponent(std::make_shared<Transform>(std::shared_ptr<GameObject>(this)));
}

GameObject::GameObject(const GameObject& gameObject)
{
	for(auto it: gameObject.m_components)
	{
		this->AddComponent(it);
	}
}

void GameObject::OnStart()
{
	for(auto it: m_components)
	{
		it->OnStart();
	}
}

void GameObject::OnFixedIterate()
{
	for(std::shared_ptr<Component> it : m_components)
	{
		it->OnFixedIterate();
	}
}

void GameObject::OnIterate()
{
	for(std::shared_ptr<Component> it : m_components)
	{
		it->OnIterate();
	}
}

void GameObject::OnDraw(SDL_Renderer* renderer)
{
	for(std::shared_ptr<Component> it : m_components)
	{
		it->OnDraw(renderer);
	}
}

void GameObject::OnEvent(SDL_Event* event)
{
	for(std::shared_ptr<Component> it : m_components)
	{
		it->OnEvent(event);
	}
}

void GameObject::OnCollisionEnter(std::shared_ptr<GameObject> obj)
{

}

const std::shared_ptr<Component>& GameObject::GetComponent(int index) const
{
	return m_components[index];
}

const std::shared_ptr<Component>& GameObject::GetComponent(const std::string& name) const
{
	auto ans = this->m_comp_map.find(name);
	if(ans == m_comp_map.end())
	{
		return NULL;
	}
	return ans->second;
}

bool GameObject::AddComponent(std::shared_ptr<Component> component)
{
	if(m_comp_map.count(component->GetName()) == 0)
	{
		m_components.push_back(component);
		m_comp_map.insert({component->GetName(), component});
		return true;
	}
	return false;
}

std::shared_ptr<Component> GameObject::GetTransform()
{
	return m_components[0];
}
