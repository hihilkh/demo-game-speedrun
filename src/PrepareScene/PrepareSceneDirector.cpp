﻿#include "GE/GEHeader.h"
#include "PrepareSceneDirector.h"

#include "Prefab/Camera/UICameraPrefab.h"

#include "Scene/TitleScene.h"

namespace PrepareScene
{
	Director::Director(GameObject& gameObject) :
		Component(gameObject)
	{
	}

	void Director::Start()
	{
		DEBUG_LOG("ゲーム全体に必要なことを用意する。");

		GE::InstantiatePersistent(Prefab::Camera::UICameraPrefab());

		DEBUG_LOG("ゲーム全体に必要なことを用意済み。Title Sceneに遷移する。");
		GE::LoadScene(Scene::titleSceneName);
	}
}