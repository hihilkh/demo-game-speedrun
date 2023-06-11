#include "GE/GEHeader.h"
#include "GameSceneDirector.h"

#include "GE/Input/InputSystem.h"
#include "Scene/Builder/EndingScene.h"
#include "Scene/SceneTransition.h"

namespace GameScene
{
	Director::Director(GameObject& gameObject) :
		Component(gameObject)
	{
	}

	void Director::Start()
	{
		DEBUG_LOG("GameScene");
	}

	void Director::Update()
	{
		if (GE::Input::GetKeyDown(GE::Input::Key::x)) {
			Scene::FadeOutAndChangeScene(Scene::endingSceneName);
		}
	}
}