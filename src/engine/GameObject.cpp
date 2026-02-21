#include "engine/GameObject.h"
#include "engine/Components/Transform.h"

GameObject::GameObject(std::string name)
{
	this->m_name = name;
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

void GameObject::OnCollisionEnter(GameObject obj)
{

}

const std::shared_ptr<Component>& GameObject::GetComponent(int index) const
{
	return m_components[index];
}

const std::shared_ptr<Component>& GameObject::GetComponent(const std::string& name) const
{
	int size = m_components.size();
	for(int i = 0; i < size; ++i)
	{
		if(m_components[i]->GetName() == name)
		{
			return m_components[i];
		}
	}

	return NULL;
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	m_components.push_back(component);
}
