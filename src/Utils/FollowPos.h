#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"

namespace Utils
{
	class FollowPos : public Component
	{
	public:
		FollowPos(GameObject& gameObject);
		void SetTarget(const Transform2D& target, const Vector2& offset = Vector2::zero);
		void ClearTarget();

	protected:
		void LateUpdate() override;
		void EndOfFrame() override;

	private:
		const Transform2D* target;
		Vector2 offset;
	};
}