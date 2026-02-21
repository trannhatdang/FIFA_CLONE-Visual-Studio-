#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "engine/Components/Component.h"

class Rigidbody : public Component
{
	public:
		Rigidbody(GameObject* gameObject);
		~Rigidbody();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
