#include "GE/GEHeader.h"
#include "SceneMapping.h"
#include "GE/Scene/Scene.h"

#include "Builder/PrepareScene.h"
#include "Builder/TitleScene.h"
#include "Builder/EndingScene.h"

namespace Scene
{
	GE::SceneManagement::SceneConfig CreateSceneConfig()
	{
		GE::SceneManagement::SceneConfig sceneConfig;
		sceneConfig.builderMap.emplace(prepareSceneName, PrepareScene());
		sceneConfig.builderMap.emplace(titleSceneName, TitleScene());
		sceneConfig.builderMap.emplace(endingSceneName, EndingScene());

		sceneConfig.firstSceneName = prepareSceneName;

		return sceneConfig;
	}
}