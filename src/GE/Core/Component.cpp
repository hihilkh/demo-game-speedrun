#include "Component.h"
#include "GameObject.h"
#include "Coroutine.h"
#include <algorithm>

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
		UpdateCoroutines();
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

	const Transform2D& Component::GetTransform() const
	{
		return gameObject.GetTransform();
	}

	Transform2D& Component::GetTransform()
	{
		return gameObject.GetTransform();
	}

	std::weak_ptr<Coroutine> Component::StartCoroutine(const std::function<bool()>& predicate, const std::function<void()>& func)
	{
		struct SharedPtrEnabler : public Coroutine
		{
			SharedPtrEnabler(const std::function<bool()>& predicate, const std::function<void()>& func) :
				Coroutine(predicate, func)
			{
			}
		};

		return coroutines.emplace_back(std::make_shared<SharedPtrEnabler>(predicate, func));
	}

	void Component::StopCoroutine(std::weak_ptr<Coroutine> coroutine)
	{
		if (coroutine.expired()) {
			return;
		}

		std::shared_ptr<Coroutine> sharedCoroutine = coroutine.lock();
		for (auto it = coroutines.begin(); it != coroutines.end(); ++it) {
			if (*it == sharedCoroutine) {
				coroutines.erase(it);
				return;
			}
		}
	}

	void Component::StopAllCoroutines()
	{
		coroutines.clear();
	}

	void Component::UpdateCoroutines()
	{
		if (coroutines.size() == 0) {
			return;
		}

		auto removeIt = std::remove_if(
			coroutines.begin(),
			coroutines.end(),
			[](auto& coroutine) { return coroutine->Update(); });
		coroutines.erase(removeIt, coroutines.end());
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