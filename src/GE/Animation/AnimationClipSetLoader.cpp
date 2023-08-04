#include "AnimationClipSetLoader.h"
#include "AnimationClip.h"
#include "AnimationKey.h"
#include "AnimationClipSet.h"
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
		const std::string animationTypeNode = "anim_type";
		const std::string imgSrcRectNode = "img_src_rect";
		const std::string posXNode = "x";
		const std::string posYNode = "y";
		const std::string wideNode = "w";
		const std::string heightNode = "h";
	}

	namespace
	{
		RectPixel ConvertToRectPixel(const GE::Json::Value& json)
		{
			return RectPixel(
				json[posXNode].asInt(),
				json[posYNode].asInt(),
				json[wideNode].asInt(),
				json[heightNode].asInt()
			);
		}

		AnimationKey ConvertToAnimationKey(const GE::Json::Value& json)
		{
			AnimationKey animKey;
			animKey.animType = static_cast<AnimationKey::AnimationType>(json[animationTypeNode].asInt());
			animKey.imgSrcRect = ConvertToRectPixel(json[imgSrcRectNode]);

			return animKey;
		}
	}

	std::unordered_map<std::string, std::weak_ptr<AnimationClipSet>> AnimationClipSetLoader::loadedClipSets;

	std::shared_ptr<AnimationClipSet> AnimationClipSetLoader::Load(const std::string& animationFile)
	{
		if (auto cache = loadedClipSets.find(animationFile); cache != loadedClipSets.end()) {
			if (!cache->second.expired()) {
				return cache->second.lock();
			}
		}

		std::vector<AnimationClip> clips;

		auto json = GE::Json::LoadJson(animationFile);
		const auto& clipsJson = json[clipsNode];

		clips.reserve(clipsJson.size());

		for (const auto& clipJson : clipsJson) {
			std::string name = clipJson[nameNode].asString();
			bool isLoop = clipJson[loopNode].asBool();
			AnimationClip animClip(name, isLoop);

			const auto& framesJson = clipJson[framesNode];
			for (const auto& frameJson : framesJson) {
				animClip.keysInFrame.emplace(frameJson[startFrameNode].asInt(), ConvertToAnimationKey(frameJson[keyNode]));
			}

			animClip.PostConstruct();
			clips.emplace_back(std::move(animClip));
		}
		
		auto clipSet = std::make_shared<AnimationClipSet>(std::move(clips));
		loadedClipSets[animationFile] = clipSet;

		return clipSet;
	}
}