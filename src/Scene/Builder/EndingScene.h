#pragma once

#include <memory>
#include <string>

namespace GE::Scene
{
	class Scene;
}

namespace Scene
{
	inline const std::string endingSceneName = "Ending";

	class EndingScene
	{
	public:
		std::unique_ptr<GE::Scene::Scene> operator()() const;
	};
}
