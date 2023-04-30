#include "GameEngine.h"
#include "Time.h"
#include "Debug/Log.h"
#include "Scene.h"

namespace GE
{
	GEConfig GameEngine::config;
	bool GameEngine::isStarted = false;

	std::vector<Scene> GameEngine::loadedScenes;
	std::unique_ptr<Scene> GameEngine::sceneToLoad;

	// 参考：https://learn.microsoft.com/en-us/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp?view=msvc-170
	int GameEngine::Start(HINSTANCE hInstance, int nCmdShow, Scene&& scene)
	{
		if (isStarted) {
			return 0;
		}

		isStarted = true;

		Init(std::move(scene));

		HWND hWnd = CreateGameWindow(hInstance);
		if (!hWnd) {
			return 0;
		}

		// The parameters to ShowWindow explained:
		// hWnd: the value returned from CreateWindow
		// nCmdShow: the fourth parameter from WinMain
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		// Main loop
		MSG msg;
		while (true) {
			//メッセージが来ているか
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					break;
				}

				//メッセージに応じた処理を行う
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (GetActiveWindow() == hWnd) {
				RunGameLoop();
			}
		}

		return 0;
	}

	void GameEngine::Init(Scene&& scene)
	{
		Time::Init(config.targetFps);
		RequestChangeScene(std::move(scene));
	}

	void GameEngine::LoadScene(Scene&& scene)
	{
		RequestChangeScene(std::move(scene));
	}

	void GameEngine::RequestChangeScene(Scene&& scene)
	{
		sceneToLoad.reset();

		if (loadedScenes.empty()) {
			ChangeScene(std::move(scene));
		} else {
			sceneToLoad = std::make_unique<Scene>(std::move(scene));
			CheckAndChangeScene();
		}
	}

	void GameEngine::CheckAndChangeScene()
	{
		if (!sceneToLoad.get()) {
			return;
		}

		ChangeScene(std::move(*sceneToLoad.release()));
	}

	void GameEngine::ChangeScene(Scene&& scene)
	{
		DEBUG_LOG("シーン遷移：既存シーンのアンロード開始");

		loadedScenes.clear();
		// TODO : アセットの破棄処理

		DEBUG_LOG("シーン遷移：既存シーンのアンロード完了");

		DEBUG_LOG("シーン遷移：" << scene.GetName() << "：読み込み開始");

		scene.Init();
		loadedScenes.push_back(std::move(scene));

		DEBUG_LOG("シーン遷移：" << loadedScenes.back().GetName() << "：読み込み完了");
	}

	void GameEngine::RunGameLoop()
	{
		// TODO
		Time::Update();

		for (Scene& scene : loadedScenes) {
			scene.Update();
		}

		for (Scene& scene : loadedScenes) {
			scene.LateUpdate();
		}

		for (Scene& scene : loadedScenes) {
			scene.Render();
		}

		CheckAndChangeScene();
	}

#pragma region ゲームウィンドウ

	namespace
	{
		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message) {
				case WM_DESTROY:
					PostQuitMessage(0);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
					break;
			}

			return (LRESULT)0;
		}
	}

	HWND GameEngine::CreateGameWindow(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = config.windowClassName.c_str();
		wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

		if (!RegisterClassEx(&wcex)) {
			MessageBox(nullptr, "ウインドウ登録に失敗", nullptr, MB_OK);
			return nullptr;
		}

		HWND hWnd = CreateWindowEx(
			WS_EX_OVERLAPPEDWINDOW,                 // an optional extended window style.
			config.windowClassName.c_str(),			// the name of the application
			config.windowTitle.c_str(),				// the text that appears in the title bar
			WS_OVERLAPPEDWINDOW,					// the type of window to create
			CW_USEDEFAULT, CW_USEDEFAULT,			// initial position (x, y)
			config.screenWidth,						// initial screen width
			config.screenHeight,					// initial screen height
			nullptr,								// the parent of this window
			nullptr,								// this application does not have a menu bar
			hInstance,								// the first parameter from WinMain
			nullptr									// not used in this application
		);

		if (!hWnd) {
			MessageBox(nullptr, "ウインドウ生成に失敗", nullptr, MB_OK);
			return nullptr;
		}

		return hWnd;
	}

#pragma endregion
}

