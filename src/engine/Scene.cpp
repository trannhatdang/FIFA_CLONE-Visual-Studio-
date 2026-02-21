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
	for(auto it: m_gameObjects)
	{
		it->OnFixedIterate();
	}
}

void Scene::OnIterate()
{
	for(auto it: m_gameObjects)
	{
		it->OnIterate();
	}
}

void Scene::OnDraw(SDL_Renderer* renderer)
{
	for(auto it: m_gameObjects)
	{
		it->OnDraw(renderer);
	}
}

void Scene::OnEvent(SDL_Event* event)
{
	for(auto it: m_gameObjects)
	{
		it->OnEvent(event);
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
