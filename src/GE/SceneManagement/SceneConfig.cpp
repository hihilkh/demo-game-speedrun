#include "SceneConfig.h"
#include "GE/Debug/Log.h"

namespace GE::SceneManagement
{
	SceneBuilder* SceneConfig::GetBuilder(const std::string& sceneName)
	{
		if (auto pair = builderMap.find(sceneName); pair != builderMap.end()) {
			return &pair->second;
		} else {
			DEBUG_LOG_WARNING("シーン： " << sceneName << " のビルダーが探せない。");
			return nullptr;
		}
	}
}