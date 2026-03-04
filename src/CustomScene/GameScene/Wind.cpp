#include "CustomScene/GameScene/Wind.h"
#include "engine/GameObject.h"


Wind::Wind(GameObject* obj) : Component("Wind", obj)
{

}

void Wind::OnIterate()
{

}

void Wind::OnFixedIterate()
{
	auto rb = (Rigidbody*)gameObject->GetComponent("Rigidbody");
	if(rb->GetVelocity().magnitude() < 5)
	{
		rb->AddVelocity(0.01f*m_speed);
		//std::cout << rb->GetVelocity() << std::endl;
	}
}

std::unique_ptr<Component> Wind::copy()
{
	return std::make_unique<Wind>(gameObject);
}

Vector3f Wind::GetWindSpeed() const
{
	return m_speed;
}

void Wind::SetWindSpeed(const Vector3f& spd)
{
	m_speed = spd;
}

void Wind::Reset()
{
	m_speed = {0, 0, 0};
}
