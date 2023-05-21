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
			auto parentWorldTransform = gameObject.Parent()->GetTransform().GetWorldTransformData();
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
			rot = worldRot - gameObject.Parent()->GetTransform().GetWorldRot();
		} else {
			rot = worldRot;
		}
	}

	Vector2 Transform2D::GetWorldPos() const
	{
		if (gameObject.Parent()) {
			return GetWorldPos(gameObject.Parent()->GetTransform().GetWorldTransformData());
		} else {
			return pos;
		}
	}

	Vector2 Transform2D::GetWorldPos(const Transform2DData& parentWorldTransformData) const
	{
		Vector2 worldPos = pos;
		if (parentWorldTransformData.rot != 0.0f) {
			worldPos.Rotate(parentWorldTransformData.rot);
		}
		worldPos += parentWorldTransformData.pos;
		return worldPos;
	}

	float Transform2D::GetWorldRot() const
	{
		if (gameObject.Parent()) {
			return GetWorldRot(gameObject.Parent()->GetTransform().GetWorldRot());
		} else {
			return rot;
		}
	}

	float Transform2D::GetWorldRot(float parentWorldRot) const
	{
		return rot + parentWorldRot;
	}

	Transform2DData Transform2D::GetWorldTransformData() const
	{
		if (gameObject.Parent()) {
			auto parentWorldTransformData = gameObject.Parent()->GetTransform().GetWorldTransformData();
			return Transform2DData(
				GetWorldPos(parentWorldTransformData),
				GetWorldRot(parentWorldTransformData.rot));
		} else {
			return Transform2DData(pos, rot);
		}
	}
}