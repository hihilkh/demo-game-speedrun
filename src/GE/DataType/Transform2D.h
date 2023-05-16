#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include "Vector2.h"

namespace GE
{
	class Transform2D : public Component
	{
	public:

		explicit Transform2D(
			GameObject& gameObject,
			const Vector2& pos = Vector2::zero,
			float rot = 0.0f,
			const Vector2& scale = Vector2::one);

		Vector2 pos;
		float rot;
		Vector2 scale;

		void SetWorldPos(const Vector2& pos);
		void SetWorldRot(float rot);
		void SetWorldScale(const Vector2& scale);

		Vector2 GetWorldPos() const;
		float GetWorldRot() const;
		Vector2 GetWorldScale() const;
	};
}