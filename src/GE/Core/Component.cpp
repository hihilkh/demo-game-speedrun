#include "Component.h"
#include "GameObject.h"

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
		if (!isEnable || !IsValid()) {
			return;
		}

		Update();
	}

	void Component::OnLateUpdate()
	{
		if (!isEnable || !IsValid()) {
			return;
		}

		LateUpdate();
	}

	void Component::OnEndOfFrame()
	{
		if (!isEnable || !IsValid()) {
			return;
		}

		EndOfFrame();
	}

	void Component::OnDestroy()
	{
		gameObject.RemoveComponentImmediate(*this);
	}

	bool Component::CheckIsInActiveScene()
	{
		return gameObject.CheckIsInActiveScene();
	}

	const Transform2D& Component::GetTransform() const
	{
		return gameObject.GetTransform();
	}

	Transform2D& Component::GetTransform()
	{
		return gameObject.GetTransform();
	}

	bool operator==(const Component& lhs, const Component& rhs)
	{
		return &lhs == &rhs;
	}

	bool operator!=(const Component& lhs, const Component& rhs)
	{
		return !(lhs == rhs);
	}
}