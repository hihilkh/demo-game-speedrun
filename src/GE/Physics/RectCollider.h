#pragma once

#include "Collider.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Rect.h"

namespace GE::Physics
{
	class RectCollider : public Collider
	{
	public:
		RectCollider(GameObject& gameObject, bool isTrigger, const Rect& rect);

		const Rect& GetRect() const { return rect; }
		void SetRect(const Rect& rect) { this->rect = rect; }

	private:
		Rect rect;
	};
}