#include "GE/GEHeader.h"
#include "SceneMapping.h"
#include "GE/Scene/Scene.h"

#include "PrepareScene.h"
#include "TitleScene.h"

namespace Scene
{
	GE::Scene::SceneConfig CreateSceneConfig()
	{
		GE::Scene::SceneConfig sceneConfig;
		sceneConfig.builderMap.emplace(prepareSceneName, PrepareScene());
		sceneConfig.builderMap.emplace(titleSceneName, TitleScene());

		sceneConfig.firstSceneName = prepareSceneName;

		return sceneConfig;
	}
}