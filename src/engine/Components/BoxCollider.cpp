#include "engine/Components/BoxCollider.h"
#include "engine/GameObject.h"

static bool PointInBetweenPoints(int in, int l, int r)
{
	return in >= l && in <= r;
}

static bool CompareBox(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off)
{
	int box_min_x = pos.x;
	int box_max_x = pos.x + off.w;
	int box_min_y = pos.y;
	int box_max_y = pos.y + off.h;

	int other_box_min_x = other_pos.x;
	int other_box_max_x = other_pos.x + other_off.w;
	int other_box_min_y = other_pos.y;
	int other_box_max_y = other_pos.y + other_off.h;

	return (PointInBetweenPoints(box_min_x, other_box_min_x, other_box_max_x) || PointInBetweenPoints(box_max_x, other_box_min_x, other_box_max_x))
		&& (PointInBetweenPoints(box_min_y, other_box_min_y, other_box_max_y) || PointInBetweenPoints(box_max_y, other_box_min_y, other_box_max_y));
}

static int FindMinDist(int LDist, int RDist, int TDist, int BDist)
{
	LDist = std::abs(LDist);
	RDist = std::abs(RDist);
	TDist = std::abs(TDist);
	BDist = std::abs(BDist);

	if(LDist <= RDist && LDist <= TDist && LDist <= BDist)
	{
		return 0;
	}
	else if(RDist <= LDist && RDist <= TDist && RDist <= BDist)
	{
		return 1;
	}
	else if(TDist <= LDist && TDist <= RDist && TDist <= BDist)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

static PointDistInfo FindDistanceFromPointToEdgeOfBox(Vector3 pos, Vector3 other_pos, BColliderOff other_off)
{
	int other_box_min_x = other_pos.x;
	int other_box_max_x = other_pos.x + other_off.w;
	int other_box_min_y = other_pos.y;
	int other_box_max_y = other_pos.y + other_off.h;

	if(!PointInBetweenPoints(pos.x, other_box_min_x, other_box_max_x) || !PointInBetweenPoints(pos.y, other_box_min_y, other_box_max_y))
	{
		return {false, false, 0};
	}

	int LDist = other_box_min_x - pos.x;
	int RDist = other_box_max_x - pos.x;
	int TDist = other_box_min_y - pos.y;
	int BDist = other_box_max_y - pos.y;

	int res = FindMinDist(LDist, RDist, TDist, BDist);

	switch(res)
	{
		case 0:
			return {true, true, LDist};
			break;
		case 1:
			return {true, true, RDist};
			break;
		case 2:
			return {true, false, TDist};
			break;
		default:
			return {true, false, BDist};
			break;
	}
}

void BoxCollider::MoveToFixedPosition(Vector3 pos, PointDistInfo info)
{
	Transform* tfs = gameObject->GetTransform();
	if(info.isX)
	{
		pos += Vector3(info.dist, 0, 0);
		tfs->SetPosition(pos);
	}
	else
	{
		pos += Vector3(0, info.dist, 0);
		tfs->SetPosition(pos);
	}
}

BoxCollider::BoxCollider(GameObject* gameObject, const BColliderOff& offset, bool isTrigger) : Component("BoxCollider", gameObject), m_offset(offset), m_trigger(isTrigger) {}

void BoxCollider::OnStart()
{

}

void BoxCollider::OnIterate()
{
	SDL_Event box_event;
	box_event.type = BOX_POS_EVENT;

	Vector3 pos = static_cast<Transform*>(gameObject->GetTransform())->GetPosition();
	box_event.user.data1 = gameObject;

	if(SDL_PushEvent(&box_event) <= 0)
	{
		SDL_Log("Pushing event failed: %s", SDL_GetError());
	};
}

void BoxCollider::OnDraw(SDL_Renderer* renderer)
{
	if(!m_debug) return;

	auto pos = gameObject->GetTransform()->GetPosition();

	SDL_FRect rect = {(float)pos.x, (float)pos.y, (float)m_offset.w, (float)m_offset.h};

	if(!SDL_RenderRect(renderer, &rect))
	{
		SDL_Log("Rendering Box Collider Debug Rect failed: %s", SDL_GetError());
	}
}

void BoxCollider::OnEvent(SDL_Event* event)
{
	if(event->type == BOX_POS_EVENT)
	{
		GameObject* other_obj = (GameObject*)(event->user.data1);
		if(other_obj == gameObject) return;

		Component* other_col_uncasted = other_obj->GetComponent("BoxCollider");

		if(other_col_uncasted == NULL) // No collision
		{
			return;
		}

		auto other_col = (BoxCollider*)other_col_uncasted;

		auto pos = static_cast<Transform*>(gameObject->GetTransform())->GetPosition();
		auto other_pos = ((Transform*)(other_obj->GetTransform()))->GetPosition();
		auto other_off = other_col->GetOffset();

		if(!CompareBox(pos, m_offset, other_pos, other_off)) return; //No collision

		if(m_trigger)
		{
			gameObject->OnTriggerEnter(other_obj);
			other_obj->OnTriggerEnter(gameObject);
		}
		else
		{
			gameObject->OnCollisionEnter(other_obj);
			other_obj->OnCollisionEnter(gameObject);
			DoCollision(pos, m_offset, other_pos, other_off);
		}
	}

	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(keyEvent.key == SDLK_F)
		{
			m_debug = !m_debug;
		}
	}
}

void BoxCollider::DoCollision(Vector3 pos, BColliderOff off, Vector3 other_pos, BColliderOff other_off)
{
	if(gameObject->GetComponent("Rigidbody") == NULL) return; //if gameobject does not have a rigidbody, it stays still

	Vector3 vertex0 = pos;
	Vector3 vertex1 = pos + Vector3(off.w, 0, 0);
	Vector3 vertex2 = pos + Vector3(off.w, off.h, 0);
	Vector3 vertex3 = pos + Vector3(0, off.h, 0);

	int other_box_min_x = other_pos.x;
	int other_box_max_x = other_pos.x + other_off.w;
	int other_box_min_y = other_pos.y;
	int other_box_max_y = other_pos.y + other_off.h;

	PointDistInfo vertex0_dist = FindDistanceFromPointToEdgeOfBox(vertex0, other_pos, other_off);
	PointDistInfo vertex1_dist = FindDistanceFromPointToEdgeOfBox(vertex1, other_pos, other_off);
	PointDistInfo vertex2_dist = FindDistanceFromPointToEdgeOfBox(vertex2, other_pos, other_off);
	PointDistInfo vertex3_dist = FindDistanceFromPointToEdgeOfBox(vertex3, other_pos, other_off);

	if(vertex0_dist.isIn) std::cout << vertex0_dist.dist << std::endl;
	if(vertex1_dist.isIn) std::cout << vertex1_dist.dist << std::endl;
	if(vertex2_dist.isIn) std::cout << vertex2_dist.dist << std::endl;
	if(vertex3_dist.isIn) std::cout << vertex3_dist.dist << std::endl;

	int res = FindMinDist((vertex0_dist.isIn ? vertex0_dist.dist : INT_MAX),
			(vertex1_dist.isIn ? vertex1_dist.dist : INT_MAX),
			(vertex2_dist.isIn ? vertex2_dist.dist : INT_MAX),
			(vertex3_dist.isIn ? vertex3_dist.dist : INT_MAX));
	//std::cout << "res: " << res << std::endl;

	switch(res)
	{
		case 0:
			MoveToFixedPosition(vertex0, vertex0_dist);
			break;
		case 1:
			MoveToFixedPosition(vertex1, vertex1_dist);
			break;
		case 2:
			MoveToFixedPosition(vertex2, vertex2_dist);
			break;
		default:
			MoveToFixedPosition(vertex3, vertex3_dist);
			break;
	}
}

std::unique_ptr<Component> BoxCollider::copy()
{
	return std::make_unique<BoxCollider>(gameObject, m_offset);
}

BColliderOff BoxCollider::GetOffset() const 
{
	return m_offset;
}

void BoxCollider::SetOffset(const BColliderOff& offset)
{
	m_offset = offset;
}
