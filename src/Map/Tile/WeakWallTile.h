#pragma once

#include "Tile.h"
#include "GE/DataType/Rect.h"

namespace GE
{
	namespace Collision
	{
		class Collider;
	}

	namespace Render
	{
		class Image;
	}
}

namespace Map
{
	class WeakWallTile : public Tile
	{
	public:
		// TODO : Animatorで制御する
		static const RectPixel normalImgSrcRect;
		static const RectPixel brokenImgSrcRect;

	public:
		explicit WeakWallTile(GameObject& gameObject, GE::Collision::Collider& collider, GE::Render::Image& image);
		void Break();

	private:
		bool isBroken;
		GE::Collision::Collider& collider;
		GE::Render::Image& image;
	};
}