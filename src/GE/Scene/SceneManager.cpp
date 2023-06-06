#include "SceneManager.h"
#include "GE/Debug/Log.h"

// 備考：現段階シングルシーンしか支援しない
namespace GE::Scene
{
	SceneConfig SceneManager::config;

	// 常にactiveSceneを持っているように、ダミーシーンを作成する。
	// でも、シーンを遷移しているとき、activeSceneを無効になる場合もある。
	// TODO : シーンの遷移手順をロックする
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

			DEBUG_LOG("シーン遷移：" << sceneNameToDestroy << "：アンロード完了");
		}

		DEBUG_LOG("シーン遷移：" << sceneName << "：読み込み開始");

		activeScene = (*builder)();
		activeScene->Load();

		DEBUG_LOG("シーン遷移：" << sceneName << "：読み込み完了。");
	}
}