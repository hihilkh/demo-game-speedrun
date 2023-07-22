#include "AnimationFactory.h"
#include "AnimationClip.h"
#include "AnimationKey.h"
#include "GE/Utils/Json.h"

namespace GE::Animation
{
	namespace
	{
		const std::string clipsNode = "clips";
		const std::string nameNode = "name";
		const std::string loopNode = "loop";

		const std::string framesNode = "frames";

		const std::string startFrameNode = "start_frame";

		const std::string keyNode = "key";
		const std::string imgSrcRectNode = "img_src_rect";
		const std::string posXNode = "x";
		const std::string posYNode = "y";
		const std::string wideNode = "w";
		const std::string heightNode = "h";
	}

	namespace
	{
		RectPixel GenerateRectPixel(const GE::Json::Value& value)
		{
			return RectPixel(
				value[posXNode].asInt(),
				value[posYNode].asInt(),
				value[wideNode].asInt(),
				value[heightNode].asInt()
			);
		}

		AnimationKey GenerateKey(const GE::Json::Value& value)
		{
			AnimationKey animKey;

			animKey.imgSrcRect = GenerateRectPixel(value[imgSrcRectNode]);

			return animKey;
		}
	}

	std::vector<AnimationClip> AnimationFactory::GenerateClips(const std::string& animationFile)
	{
		std::vector<AnimationClip> result;

		auto value = GE::Json::LoadJson(animationFile);
		const auto& clips = value[clipsNode];

		result.reserve(clips.size());

		for (const auto& clip : clips) {
			std::string name = clip[nameNode].asString();
			bool isLoop = clip[loopNode].asBool();
			AnimationClip animClip(name, isLoop);

			const auto& frames = clip[framesNode];
			for (const auto& frame : frames) {
				animClip.keysInFrame.emplace(frame[startFrameNode].asInt(), GenerateKey(frame[keyNode]));
			}

			animClip.PostConstruct();
			result.emplace_back(std::move(animClip));
		}
		
		return result;
	}
}