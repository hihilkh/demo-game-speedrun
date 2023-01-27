#pragma once

#include <GameEngine_Ver3_83.h>

namespace ParticleSystem
{
	struct ParticleConfig
	{
		typedef shared_ptr<ParticleConfig> SP;

		DG::Image::SP img;
		ML::Box2D src;
		ML::Box2D drawBase;
		ML::Vec2 posBase;
		float randomPosHalfRange;		// 正方形 (例えば、x成分 : [posBase.x - randomPosHalfRange, posBase.x + randomPosHalfRange])
		ML::Vec2 imgRotationRange;		// デグリー
		ML::Vec2 emitAngleRange;		// デグリー
		float emitSpeed;
		bool hasGravity;

		ParticleConfig(DG::Image::SP img, const ML::Box2D& src, const ML::Box2D& drawBase, const ML::Vec2& posBase);

		ML::Vec2 GetRandomPos() const;
		float GetRandomImgRotation() const;
		ML::Vec2 GetImgRotationCenter() const;
		ML::Vec2 GetRandomMoveVec() const;
	};
}