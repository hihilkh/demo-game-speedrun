#include "ParticleConfig.h"
#include "GE/Utils/Math.h"

namespace ParticleSystem
{
	ParticleConfig::ParticleConfig(DG::Image::SP img, const ML::Box2D& src, const ML::Box2D& drawBase, const ML::Vec2& posBase) :
		img(img),
		src(src),
		drawBase(drawBase),
		posBase(posBase),
		randomPosHalfRange(0),
		imgRotationRange(ML::Vec2(0.0f, 360.0f)),
		emitAngleRange(ML::Vec2(0.0f, 360.0f)),
		emitSpeed(0),
		hasGravity(false)
	{
	}

	ML::Vec2 ParticleConfig::GetRandomPos() const
	{
		return ML::Vec2(
			Math::GetRandom(posBase.x - randomPosHalfRange, posBase.x + randomPosHalfRange),
			Math::GetRandom(posBase.y - randomPosHalfRange, posBase.y + randomPosHalfRange));
	}

	/// <returns>ラジアン</returns>
	float ParticleConfig::GetRandomImgRotation() const
	{
		return ML::ToRadian(Math::GetRandom(imgRotationRange.x, imgRotationRange.y));
	}
	ML::Vec2 ParticleConfig::GetImgRotationCenter() const
	{
		return ML::Vec2(drawBase.w / 2.0f, drawBase.h / 2.0f);
	}

	ML::Vec2 ParticleConfig::GetRandomMoveVec() const
	{
		float emitAngle = ML::ToRadian(Math::GetRandom(emitAngleRange.x, emitAngleRange.y));
		return ML::Vec2(cos(emitAngle) * emitSpeed, sin(emitAngle) * emitSpeed);
	}
}