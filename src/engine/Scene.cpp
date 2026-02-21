#include "engine/Scene.h"

Scene::Scene(const std::string& name, void (*changeSceneCallback)(int), SDL_Renderer* renderer, SDL_Window* window) : m_name(name), m_changeSceneCallback(changeSceneCallback), m_renderer(renderer), m_window(window) 
{
}

Scene::~Scene()
{

}

void Scene::OnStart()
{
	for(auto it: m_gameObjects)
	{
		it->OnStart();
	}
}

void Scene::OnFixedIterate()
{
	int size = m_gameObjects.size();
	for(int i = 0; i < size; ++i)
	{
		m_gameObjects[i]->OnFixedIterate();
	}
}

void Scene::OnIterate()
{
	int size = m_gameObjects.size();
	for(int i = 0; i < size; ++i)
	{
		m_gameObjects[i]->OnIterate();
	}
}

void Scene::OnDraw(SDL_Renderer* renderer)
{
	int size = m_gameObjects.size();
	for(int i = 0; i < size; ++i)
	{
		m_gameObjects[i]->OnDraw(renderer);
	}
}

void Scene::OnEvent(SDL_Event* event)
{
	int size = m_gameObjects.size();
	for(int i = 0; i < size; ++i)
	{
		m_gameObjects[i]->OnEvent(event);
	}
}

void Scene::AddGameObject()
{
	this->m_gameObjects.push_back(std::make_unique<GameObject>());
}

std::shared_ptr<GameObject>& Scene::GetGameObject(int index)
{
	return this->m_gameObjects[index];
}

SDL_Renderer* Scene::GetRenderer() const 
{
	return m_renderer;
}

SDL_Window* Scene::GetWindow() const
{
	return m_window;
}
