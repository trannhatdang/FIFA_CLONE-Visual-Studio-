#include "engine/Components/Transform.h"

Transform::Transform(const std::shared_ptr<GameObject>& gameObject, const Vector3& pos, const Vector3& rot) : Component("Transform", gameObject), m_pos(pos), m_rot(rot)
{

}

void Transform::OnIterate()
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
