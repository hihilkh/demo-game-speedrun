#include "GEHeader.h"
#include "SceneMapping.h"
#include "TitleScene.h"

namespace Scene
{
	GE::SceneManagement::SceneConfig CreateSceneConfig()
	{
		GE::SceneManagement::SceneConfig sceneConfig;
		sceneConfig.builderMap.emplace(titleSceneName, TitleScene());

		sceneConfig.firstSceneName = titleSceneName;

		return sceneConfig;
	}
}