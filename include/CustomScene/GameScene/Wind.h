#ifndef WIND_H_
#define WIND_H_

#include "engine/Components/Component.h"
#include "engine/Components/Rigidbody.h"

class Wind : public Component
{
	private:
		Vector3f m_speed = { 0, 0, 0 };
	public:
		Wind(GameObject* obj);
		void OnIterate();
		void OnFixedIterate();
		std::unique_ptr<Component> copy();
		Vector3f GetWindSpeed() const;
		void SetWindSpeed(const Vector3f& spd);
		void Reset();
};

#endif
