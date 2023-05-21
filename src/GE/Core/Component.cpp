#include "Component.h"
#include "gameObject.h"

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

	const Transform2D& Component::GetTransform() const
	{
		return gameObject.GetTransform();
	}

	Transform2D& Component::GetTransform()
	{
		return gameObject.GetTransform();
	}
}