#pragma once

#include <memory>
#include <string>

namespace GE
{
	class Scene;
}

namespace Scene
{
	inline const std::string prepareSceneName = "PrepareScene";

	class PrepareScene
	{
	public:
		std::unique_ptr<GE::Scene> operator()() const;
	};
}
