#include "engine/Components/Transform.h"

Transform::Transform(const std::shared_ptr<GameObject>& gameObject, const Vector3& pos, const Vector3& rot) : Component("Transform", gameObject), m_pos(pos), m_rot(rot)
{

}

void Transform::OnStart()
{

}

void Transform::OnIterate()
{

}

void Transform::OnDraw(SDL_Renderer* renderer)
{

}

void Transform::OnEvent(SDL_Event* event)
{

}

const Vector3& Transform::GetPosition() const
{
	return m_pos;
}

void Transform::SetPosition(const Vector3& pos)
{
	m_pos = pos;
}
