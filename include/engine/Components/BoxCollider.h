#ifndef B_COLLIDER_H_
#define B_COLLIDER_H_

#include "engine/Components/Component.h"
#include "Rigidbody.h"
#include <algorithm>

//Only 2D and only box, normally this should inherit another collider component but this should do

typedef struct BColliderOff
{
	int w_off;
	int h_off;
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
		bool m_trigger;
		BColliderOff m_offset;
		std::unordered_map<GameObject*, bool> m_objectsTouching;

		void MoveToFixedPosition(Vector3 pos, PointDistInfo info);
	public:
		BoxCollider(GameObject* gameObject, const BColliderOff& offset);
		void OnStart();
		void OnIterate();
		void OnEvent(SDL_Event* event);
		void FixPosition(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off);
		std::unique_ptr<Component> copy();
		BColliderOff GetOffset() const;
		void SetOffset(const BColliderOff& offset);
};

#endif
