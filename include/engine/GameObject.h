#ifndef G_OBJECT_
#define G_OBJECT_

#include "Components/Component.h"
#include <unordered_map>
class Transform;

class GameObject
{
	private:
		std::vector<std::shared_ptr<Component>> m_components;
		std::string m_name;
		std::string m_tag;
		std::unordered_map<std::string, std::shared_ptr<Component>> m_comp_map;
	public:
		GameObject(std::string name = "GameObject", std::string tag = "Entity");
		GameObject(const GameObject& gameObject);
		void OnStart();
		void OnIterate();
		void OnFixedIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		void OnCollisionEnter(GameObject obj);
		const std::shared_ptr<Component>& GetComponent(int index) const;
		const std::shared_ptr<Component>& GetComponent(const std::string& name) const;
		bool AddComponent(std::shared_ptr<Component> component);
		std::shared_ptr<Component> GetTransform();
};

#endif
