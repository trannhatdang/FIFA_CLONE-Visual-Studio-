#ifndef SCENE_H_
#define SCENE_H_

#include "GameObject.h"

class Scene
{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;
		std::string m_name;
		void (*m_changeSceneCallback)(int);
		SDL_Renderer* m_renderer;
		SDL_Window* m_window;
	public:
		Scene(const std::string& name = "Scene", void (*changeSceneCallback)(int) = nullptr, SDL_Renderer* renderer = nullptr, SDL_Window* window = nullptr);
		~Scene();
		void OnStart();
		void OnIterate();
		void OnFixedIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		void AddGameObject();
		std::shared_ptr<GameObject>& GetGameObject(int index = 0);
		SDL_Renderer* GetRenderer() const;
		SDL_Window* GetWindow() const;
};

#endif
