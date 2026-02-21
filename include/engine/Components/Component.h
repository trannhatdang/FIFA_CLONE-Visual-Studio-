#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "engine/dg_engine_std.h"
#include <unordered_map>
class GameObject;

class Component
{
	protected:
		std::string m_name = "Component";
		std::shared_ptr<GameObject> gameObject;
	public:
		Component(const std::string& name, const std::shared_ptr<GameObject>& gameObject);
		virtual void OnStart();
		virtual void OnFixedIterate();
		virtual void OnIterate() = 0;
		virtual void OnDraw(SDL_Renderer* renderer);
		virtual void OnEvent(SDL_Event* event);
		std::string GetName() const;
};

#endif
