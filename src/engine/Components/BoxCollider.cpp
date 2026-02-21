#include "engine/Components/BoxCollider.h"

BoxCollider::BoxCollider(const std::shared_ptr<GameObject>& gameObject, const BColliderOff& offset) : Component("BoxCollider", gameObject), m_offset(offset) {}

void BoxCollider::OnStart()
{

}

void BoxCollider::OnIterate()
{

}

void BoxCollider::OnDraw(SDL_Renderer* renderer)
{

}

void BoxCollider::OnEvent(SDL_Event* event)
{

}

const BColliderOff& BoxCollider::GetOffset() const 
{
	return m_offset;
}

void BoxCollider::SetOffset(const BColliderOff& offset)
{
	m_offset = offset;
}
