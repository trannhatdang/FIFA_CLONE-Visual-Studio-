#ifndef B_COLLIDER_H_
#define B_COLLIDER_H_

#include "engine/Components/Component.h"
#include <algorithm>

class Rigidbody;

//Only 2D and only box, normally this should inherit another collider component but this should do

typedef struct BColliderOff
{
	int w;
	int h;
} BColliderOff;

typedef struct PointDistInfo
{
	bool isIn;
	Vector3 dist;
} PointDistInfo;

class BoxCollider : public Component
{
	private:
		bool m_trigger = false;
		bool m_debug = false;
		BColliderOff m_offset;
		std::unordered_map<GameObject*, bool> m_objectsTouching;

		void moveToFixedPosition(Vector3 pos, PointDistInfo info);
		bool checkCollision(const Vector3& pos) const;
		void checkCollisionOfCurr();
	public:
		BoxCollider(GameObject* gameObject, const BColliderOff& offset, bool isTrigger = false);
		void OnStart();
		void OnIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		void DoCollision(GameObject* other_obj);
		BColliderOff GetOffset() const;
		void SetOffset(const BColliderOff& offset);
		Vector3 CheckPath(const Vector3& pos, const Vector3f& dir) const;

		std::unique_ptr<Component> copy();
};

#endif
