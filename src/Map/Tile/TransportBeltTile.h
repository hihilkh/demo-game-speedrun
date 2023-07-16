#pragma once

#include "Tile.h"
#include "TransformUtils/Direction.h"
#include "GE/DataType/Rect.h"

namespace GE
{
	namespace Collision
	{
		class Collider;
		namespace Detection
		{
			enum class CollidedType : std::uint8_t;
		}
	}

	namespace Render
	{
		class Image;
	}
}

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
		explicit TransportBeltTile(GameObject& gameObject, GE::Collision::Collider& collider, GE::Render::Image& image);

		void SetDirection(TransformUtils::Direction direction);

	protected:
		void Start() override;
		void PreDestroy() override;

	private:
		GE::Collision::Collider& collider;
		GE::Render::Image& image;

		TransformUtils::Direction direction;

	private:
		void HandleTrigger(const GE::Collision::Collider& other, GE::Collision::Detection::CollidedType collidedType);
	};
}