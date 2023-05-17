#include "Component.h"

namespace GE
{
	Component::Component(GameObject& gameObject) : 
		gameObject(gameObject),
		isEnable(true)
	{
	}

	void Component::OnAwake()
	{
		Awake();
	}

	void Component::OnStart()
	{
		Start();
	}

	void Component::OnUpdate()
	{
		if (!isEnable) {
			return;
		}

		Update();
	}

	void Component::OnLateUpdate()
	{
		if (!isEnable) {
			return;
		}

		LateUpdate();
	}
}