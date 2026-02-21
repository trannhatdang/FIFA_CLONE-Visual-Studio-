#ifndef G_OBJECT_
#define G_OBJECT_

#include "Components/Component.h"

class GameObject
{
	private:
		std::vector<std::shared_ptr<Component>> m_components;
		std::string m_name;
	public:
		GameObject(std::string name = "GameObject");
		GameObject(const GameObject& gameObject);
		void OnStart();
		void OnIterate();
		void OnFixedIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		void OnCollisionEnter(GameObject obj);
		const std::shared_ptr<Component>& GetComponent(int index) const;
		const std::shared_ptr<Component>& GetComponent(const std::string& name) const;
		void AddComponent(std::shared_ptr<Component> component);
};

#endif
