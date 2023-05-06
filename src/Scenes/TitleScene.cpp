#include "GEHeader.h"
#include "TitleScene.h"
#include "SceneManagement/Scene.h"

namespace Scene
{
	std::unique_ptr<GE::SceneManagement::Scene> TitleScene::operator()() const
	{
		auto scene = std::make_unique<GE::SceneManagement::Scene>(titleSceneName);
		return scene;
	}
}