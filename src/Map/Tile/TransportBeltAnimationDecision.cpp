#include "GE/GEHeader.h"
#include "TransportBeltAnimationDecision.h"
#include "TransportBeltTile.h"

namespace Map
{
	namespace
	{
		std::string GetClipName(TransformUtils::Direction dir)
		{
			using namespace TransformUtils;
			switch (dir) {
				case Direction::Down:	return "down";
				case Direction::Left:	return "left";
				case Direction::Up:		return "up";
				case Direction::Right:	return "right";
			}

			assert(false && "おかしい方向");

			// 警告を出さないように
			return "";
		}
	}

	TransportBeltAnimationDecision::TransportBeltAnimationDecision(TransportBeltTile& tile) :
		GE::Animation::AnimationDecision(),
		tile(tile),
		clipName("")
	{
	}

	std::string TransportBeltAnimationDecision::DecideCurrentClip()
	{
		if (clipName == "") {
			clipName = GetClipName(tile.GetDirection());
		}

		return clipName;
	}
}