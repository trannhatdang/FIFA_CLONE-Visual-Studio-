#ifndef B_COLLIDER_H_
#define B_COLLIDER_H_

#include "engine/Components/Component.h"

//Only 2D and only box, normally this should inherit another collider component but this should do

typedef struct BColliderOff
{
	int t_off;
	int b_off;
	int l_off;
	int r_off;
} BColliderOff;

class BoxCollider : public Component
{
	private:
		BColliderOff m_offset;
	public:
		BoxCollider(const std::shared_ptr<GameObject>& gameObject, const BColliderOff& offset);
		void OnStart();
		void OnIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		const BColliderOff& GetOffset() const;
		void SetOffset(const BColliderOff& offset);
};

#endif
