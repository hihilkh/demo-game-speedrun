#include "Transform2D.h"

namespace GE
{
	Transform2D::Transform2D(GameObject& gameObject, const Vector2& pos, float rot, const Vector2& scale) :
		Component(gameObject),
		pos(pos),
		rot(rot),
		scale(scale)
	{
	}

	// TODO : Temp
	void Transform2D::SetWorldPos(const Vector2& pos)
	{
	}
	void Transform2D::SetWorldRot(float rot)
	{
	}
	void Transform2D::SetWorldScale(const Vector2& scale)
	{
	}
	Vector2 Transform2D::GetWorldPos() const
	{
		return Vector2();
	}
	float Transform2D::GetWorldRot() const
	{
		return 0.0f;
	}
	Vector2 Transform2D::GetWorldScale() const
	{
		return Vector2();
	}
}