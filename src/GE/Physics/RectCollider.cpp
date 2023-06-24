#include "RectCollider.h"

namespace GE::Physics
{
	RectCollider::RectCollider(GameObject& gameObject, bool isTrigger, const Rect& rect) :
		Collider(gameObject, isTrigger),
		rect(rect)
	{

	}
}