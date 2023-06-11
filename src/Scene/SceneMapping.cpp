#include "GE/GEHeader.h"
#include "SceneMapping.h"
#include "GE/Scene/Scene.h"

#include "Builder/PrepareScene.h"
#include "Builder/TitleScene.h"
#include "Builder/GameScene.h"
#include "Builder/EndingScene.h"

namespace Scene
{
	GE::SceneManagement::SceneConfig CreateSceneConfig()
	{
		GE::SceneManagement::SceneConfig sceneConfig;
		sceneConfig.builderMap.emplace(prepareSceneName, PrepareScene());
		sceneConfig.builderMap.emplace(titleSceneName, TitleScene());
		sceneConfig.builderMap.emplace(gameSceneName, GameScene());
		sceneConfig.builderMap.emplace(endingSceneName, EndingScene());

		sceneConfig.firstSceneName = prepareSceneName;

		return sceneConfig;
	}
}