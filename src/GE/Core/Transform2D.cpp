#include "Transform2D.h"
#include "GameObject.h"

namespace GE
{
	Transform2D::Transform2D(GameObject& gameObject, const Vector2& pos, float rot) :
		gameObject(gameObject),
		Transform2DData(pos, rot)
	{
	}

	void Transform2D::SetWorldPos(const Vector2& worldPos)
	{
		if (gameObject.Parent()) {
			auto parentWorldTransform = gameObject.Parent()->Transform().GetWorldTransformData();
			pos = worldPos;
			pos -= parentWorldTransform.pos;
			pos.Rotate(-parentWorldTransform.rot);
		} else {
			pos = worldPos;
		}
	}

	void Transform2D::SetWorldRot(float worldRot)
	{
		if (gameObject.Parent()) {
			rot = worldRot - gameObject.Parent()->Transform().GetWorldRot();
		} else {
			rot = worldRot;
		}
	}

	Vector2 Transform2D::GetWorldPos() const
	{
		if (gameObject.Parent()) {
			auto parentWorldTransform = gameObject.Parent()->Transform().GetWorldTransformData();
			Vector2 worldPos = pos;
			worldPos.Rotate(parentWorldTransform.rot);
			worldPos += parentWorldTransform.pos;
			return worldPos;
		} else {
			return pos;
		}
	}
	float Transform2D::GetWorldRot() const
	{
		if (gameObject.Parent()) {
			return gameObject.Parent()->Transform().GetWorldRot() + rot;
		} else {
			return rot;
		}
	}

	Internal::Transform2DData Transform2D::GetWorldTransformData() const
	{
		return Internal::Transform2DData(GetWorldPos(), GetWorldRot());
	}
}