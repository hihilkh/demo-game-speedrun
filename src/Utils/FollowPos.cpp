#include "GE/GEHeader.h"
#include "FollowPos.h"

namespace Utils
{
	FollowPos::FollowPos(GameObject& gameObject) :
		Component(gameObject),
		target(nullptr),
		offset(Vector2::zero)
	{
	}

	void FollowPos::SetTarget(const Transform2D& target, const Vector2& offset)
	{
		this->target = &target;
		this->offset = offset;
	}

	void FollowPos::ClearTarget()
	{
		target = nullptr;
	}

	void FollowPos::LateUpdate()
	{
		if (target == nullptr) {
			return;
		}

		GetTransform().SetWorldPos(target->GetWorldPos() + offset);
	}

	void FollowPos::EndOfFrame()
	{
		if (target == nullptr) {
			return;
		}

		if (!target->gameObject.IsValid()) {
			target = nullptr;
		}
	}
}