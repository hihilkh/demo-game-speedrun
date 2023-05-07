#include "Component.h"

namespace GE
{
	Component::Component(GameObject& gameObject) : gameObject(gameObject)
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
		if (!GetEnable()) {
			return;
		}

		Update();
	}

	void Component::OnLateUpdate()
	{
		if (!GetEnable()) {
			return;
		}

		LateUpdate();
	}
}