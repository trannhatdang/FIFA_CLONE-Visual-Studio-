#include "engine/Components/BoxCollider.h"
#include "engine/GameObject.h"

static bool PointInBetweenPoints(int in, int l, int r)
{
	return in >= l && in <= r;
}

static bool CompareBox(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off)
{
	int box_min_x = pos.x;
	int box_max_x = pos.x + off.w_off;
	int box_min_y = pos.y;
	int box_max_y = pos.y + off.h_off;

	int other_box_min_x = other_pos.x;
	int other_box_max_x = other_pos.x + other_off.w_off;
	int other_box_min_y = other_pos.y;
	int other_box_max_y = other_pos.y + other_off.h_off;
	return (PointInBetweenPoints(box_min_x, other_box_min_x, other_box_max_x) || PointInBetweenPoints(box_max_x, other_box_min_x, other_box_max_x))
		&& (PointInBetweenPoints(box_min_y, other_box_min_y, other_box_max_y) || PointInBetweenPoints(box_max_y, other_box_min_y, other_box_max_y));
}

BoxCollider::BoxCollider(GameObject* gameObject, const BColliderOff& offset) : Component("BoxCollider", gameObject), m_offset(offset) {}

void BoxCollider::OnStart()
{

}

void BoxCollider::OnIterate()
{
	SDL_Event box_event;
	box_event.type = BOX_POS_EVENT;

	Vector3 pos = static_cast<Transform*>(gameObject->GetTransform())->GetPosition();
	box_event.user.data1 = this;

	SDL_PushEvent(&box_event);
}

void BoxCollider::OnEvent(SDL_Event* event)
{
	if(event->type == BOX_POS_EVENT)
	{
		auto pos = static_cast<Transform*>(gameObject->GetTransform())->GetPosition();

		auto other_obj = (GameObject*)(event->user.data1);
		auto other_pos = ((Transform*)(other_obj->GetTransform()))->GetPosition();
		BoxCollider* other_col = (BoxCollider*)other_obj->GetComponent("BoxCollider");
		auto other_off = (BColliderOff)other_col->GetOffset();

		if(CompareBox(pos, m_offset, other_pos, other_off))
		{
			std::cout << gameObject->GetName() << " is beside " << other_obj->GetName() << '\n';
		}
	}
}

std::unique_ptr<Component> BoxCollider::copy()
{
	return std::make_unique<BoxCollider>(gameObject, m_offset);
}

const BColliderOff& BoxCollider::GetOffset() const 
{
	return m_offset;
}

void BoxCollider::SetOffset(const BColliderOff& offset)
{
	m_offset = offset;
}
