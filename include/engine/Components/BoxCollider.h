#ifndef B_COLLIDER_H_
#define B_COLLIDER_H_

#include "engine/Components/Component.h"
#include "Rigidbody.h"
#include <algorithm>

//Only 2D and only box, normally this should inherit another collider component but this should do

typedef struct BColliderOff
{
	int w;
	int h;
} BColliderOff;

typedef struct PointDistInfo
{
	bool isIn;
	bool isX;
	int dist;
} PointDistInfo;

class BoxCollider : public Component
{
	private:
		bool m_trigger = false;
		bool m_debug = false;
		BColliderOff m_offset;
		std::unordered_map<GameObject*, bool> m_objectsTouching;

		void MoveToFixedPosition(Vector3 pos, PointDistInfo info);
	public:
		BoxCollider(GameObject* gameObject, const BColliderOff& offset, bool isTrigger = false);
		void OnStart();
		void OnIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		void DoCollision(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off);
		std::unique_ptr<Component> copy();
		BColliderOff GetOffset() const;
		void SetOffset(const BColliderOff& offset);
};

#endif
