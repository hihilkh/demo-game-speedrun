#pragma once

#include <memory>
#include <string>

namespace GE::SceneManagement
{
	class Scene;
}

namespace Scene
{
	inline const std::string titleSceneName = "Title";

	class TitleScene
	{
	public:
		std::unique_ptr<GE::SceneManagement::Scene> operator()() const;
	};
}
