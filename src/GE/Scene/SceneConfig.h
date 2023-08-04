#pragma once

#include <unordered_map>
#include <functional>
#include <string>
#include <memory>

namespace GE
{
	class Scene;
}

namespace GE::SceneManagement
{
	using SceneBuilder = std::function<std::unique_ptr<Scene>()>;

	struct SceneConfig
	{
		std::unordered_map<std::string, SceneBuilder> builderMap;
		std::string firstSceneName = "";
		
		SceneBuilder* GetBuilder(const std::string& sceneName);
	};
}