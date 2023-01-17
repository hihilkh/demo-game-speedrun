#pragma once

namespace Map 
{
	enum class MapChipType
	{
		Floor = 0,
		UnbreakableWall = 1,
		WeakWall = 2,
		StrongWall = 3,
		TransportBelt = 4,
		Button = 5,
	};

	inline bool GetIsWalkable(MapChipType type)
	{
		return	type == MapChipType::Floor ||
				type == MapChipType::TransportBelt ||
				type == MapChipType::Button;
	}
}
