#include "engine/GameObject.h"
#include "engine/Components/Transform.h"

GameObject::GameObject(std::string name, std::string tag) : m_name(name), m_tag(tag)
{
	this->AddComponent(new Transform(this));
}

GameObject::GameObject(const GameObject& gameObject)
{
	for(auto i = 0; i < gameObject.m_components.size(); ++i)
	{
		this->CopyComponent(gameObject.m_components[i]);
	}
}

void GameObject::OnStart()
{
	for(auto i = 0; i < this->m_components.size(); ++i)
	{
		m_components[i]->OnStart();
	}
}

void GameObject::OnFixedIterate()
{
	for(auto i = 0; i < this->m_components.size(); ++i)
	{
		m_components[i]->OnFixedIterate();
	}
}

void GameObject::OnIterate()
{
	for(auto i = 0; i < this->m_components.size(); ++i)
	{
		m_components[i]->OnIterate();
	}
}

void GameObject::OnDraw(SDL_Renderer* renderer)
{
	for(auto i = 0; i < this->m_components.size(); ++i)
	{
		m_components[i]->OnDraw(renderer);
	}
}

void GameObject::OnEvent(SDL_Event* event)
{
	for(auto i = 0; i < this->m_components.size(); ++i)
	{
		m_components[i]->OnEvent(event);
	}
}

void GameObject::OnCollisionEnter(GameObject* obj)
{
	for(auto i = 0; i < this->m_components.size(); ++i)
	{
		m_components[i]->OnCollisionEnter(obj);
	}
}

void GameObject::OnTriggerEnter(GameObject* obj)
{
	for(auto i = 0; i < this->m_components.size(); ++i)
	{
		m_components[i]->OnTriggerEnter(obj);
	}
}

Component* GameObject::GetComponent(int index) const
{
	return m_components[index].get();
}

Component* GameObject::GetComponent(const std::string& name) const
{
	auto ans = this->m_comp_map.find(name);
	if(ans == m_comp_map.end())
	{
		return NULL;
	}
	return ans->second;
}

Transform* GameObject::GetTransform() const
{
	return static_cast<Transform*>(m_components[0].get());
}

std::string GameObject::GetName() const
{
	return this->m_name;
}

bool GameObject::AddComponent(Component* component)
{
	if(m_comp_map.count(component->GetName()) == 0)
	{
		m_components.push_back(std::unique_ptr<Component>(component));
		m_comp_map.insert({component->GetName(), component});
		return true;
	}
	return false;
}

bool GameObject::CopyComponent(const std::unique_ptr<Component>& component)
{
	if (m_comp_map.count(component->GetName()) == 0)
	{
		m_components.push_back(component->copy());
		m_comp_map.insert({component->GetName(), m_components.back().get()});
		return true;
	}
	return false;

}

