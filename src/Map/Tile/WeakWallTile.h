﻿#pragma once

#include "Tile.h"
#include "GE/DataType/Rect.h"

namespace Map
{
	class WeakWallTile : public Tile
	{
	public:
		// TODO : Animatorで制御する
		static const RectPixel normalImgSrcRect;
		static const RectPixel brokenImgSrcRect;

	public:
		explicit WeakWallTile(GameObject& gameObject, Collider& collider, Image& image);
		void Break();

	private:
		bool isBroken;
		Collider& collider;
		Image& image;
	};
}