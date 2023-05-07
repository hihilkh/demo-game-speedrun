#include "SceneManager.h"
#include "Scene.h"
#include "Debug/Log.h"


namespace GE::SceneManagement
{
	SceneConfig SceneManager::config;

	// 常にactiveSceneを持っているように、ダミーシーンを作成する
	// TODO : 今スレッドセーフではない。GetActiveScene()を呼び出す時、activeSceneはない可能がある
	std::unique_ptr<Scene> SceneManager::activeScene = std::make_unique<Scene>("Dummy");

	Scene& SceneManager::GetActiveScene()
	{
		return *activeScene;
	}

	void SceneManager::SetConfig(SceneConfig&& config)
	{
		SceneManager::config = std::move(config);
	}

	void SceneManager::LoadFirstScene()
	{
		ChangeScene(config.firstSceneName);
	}

	void SceneManager::ChangeScene(const std::string& sceneName)
	{
		SceneBuilder* builder = config.GetBuilder(sceneName);

		if (!builder) {
			DEBUG_LOG_WARNING("シーン遷移：" << sceneName << "：読み込み失敗：ビルダーがない");
			return;
		}

		if (activeScene) {
			std::string sceneNameToDestroy = activeScene->GetName();
			DEBUG_LOG("シーン遷移：" << sceneNameToDestroy << "：アンロード開始");

			activeScene.reset();
			// TODO : アセットの破棄処理

			DEBUG_LOG("シーン遷移：" << sceneNameToDestroy << "：アンロード完了");
		}

		DEBUG_LOG("シーン遷移：" << sceneName << "：読み込み開始");

		activeScene = (*builder)();

		DEBUG_LOG("シーン遷移：" << sceneName << "：読み込み完了。");
	}
}