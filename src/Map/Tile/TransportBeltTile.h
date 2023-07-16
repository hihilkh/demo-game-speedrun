#pragma once

#include "Tile.h"
#include "TransformUtils/Direction.h"
#include "GE/DataType/Rect.h"

namespace Map
{
	class TransportBeltTile : public Tile
	{
	public:
		// TODO : Animatorで制御する
		static const RectPixel downImgSrcRect;
		static const RectPixel leftImgSrcRect;
		static const RectPixel upImgSrcRect;
		static const RectPixel rightImgSrcRect;

	public:
		explicit TransportBeltTile(GameObject& gameObject, Collider& collider, Image& image);

		void SetDirection(TransformUtils::Direction direction);

	protected:
		void Start() override;
		void PreDestroy() override;

	private:
		Collider& collider;
		Image& image;

		TransformUtils::Direction direction;

	private:
		void HandleTrigger(const Collider& other, CollidedType collidedType);
	};
}