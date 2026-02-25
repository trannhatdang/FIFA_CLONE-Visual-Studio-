#include "engine/Scene.h"

Scene::Scene(const std::string& name, void (*changeSceneCallback)(int), SDL_Renderer* renderer, SDL_Window* window) : m_name(name), m_changeSceneCallback(changeSceneCallback), m_renderer(renderer), m_window(window) 
{
}

Scene::~Scene()
{

}

void Scene::OnStart()
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnStart();
	}
}

void Scene::OnFixedIterate()
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnFixedIterate();
	}
}

void Scene::OnIterate()
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnIterate();
	}
}

void Scene::OnDraw(SDL_Renderer* renderer)
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnDraw(renderer);
	}
}

void Scene::OnEvent(SDL_Event* event)
{
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->OnEvent(event);
	}
}

void Scene::AddGameObject(const std::string& name, const std::string& tag)
{
	this->m_gameObjects.push_back(std::make_unique<GameObject>(name, tag));
}

GameObject* Scene::GetGameObject(int index)
{
	return this->m_gameObjects[index].get();
}

SDL_Renderer* Scene::GetRenderer() const 
{
	return m_renderer;
}

SDL_Window* Scene::GetWindow() const
{
	return m_window;
}

void Scene::DEBUG_PrintGameObjAdd() const
{
	std::cout << "OBJ ADD: " << std::endl;
	for(auto i = 0; i < m_gameObjects.size(); ++i)
	{
		std::cout << m_gameObjects[i].get() << std::endl;
	}
}
