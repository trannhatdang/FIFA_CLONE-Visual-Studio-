#ifndef B_COLLIDER_H_
#define B_COLLIDER_H_

#include "engine/Components/Component.h"

//Only 2D and only box, normally this should inherit another collider component but this should do

typedef struct BColliderOff
{
	int w_off;
	int h_off;
} BColliderOff;

class BoxCollider : public Component
{
	private:
		BColliderOff m_offset;
		std::unordered_map<GameObject*, bool> m_objectsTouching;
	public:
		BoxCollider(GameObject* gameObject, const BColliderOff& offset);
		void OnStart();
		void OnIterate();
		void OnEvent(SDL_Event* event);
		std::unique_ptr<Component> copy();
		const BColliderOff& GetOffset() const;
		void SetOffset(const BColliderOff& offset);
};

#endif
