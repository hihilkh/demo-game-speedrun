#include "GameEngine.h"
#include "Time.h"
#include "SceneManagement/SceneManager.h"
#include "SceneManagement/Scene.h"

namespace GE
{
	GEConfig GameEngine::config;
	bool GameEngine::isStarted = false;
	std::string GameEngine::sceneNameToLoad = "";

	void GameEngine::SetSceneConfig(SceneManagement::SceneConfig&& config)
	{
		SceneManagement::SceneManager::SetConfig(std::move(config));
	}

	// 参考：https://learn.microsoft.com/en-us/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp?view=msvc-170
	int GameEngine::Start(HINSTANCE hInstance, int nCmdShow)
	{
		if (isStarted) {
			return 0;
		}

		isStarted = true;

		InitEngine();
		return StartWithWindows(hInstance, nCmdShow);
		
	}

	void GameEngine::InitEngine()
	{
		Time::Init(config.targetFps);
		SceneManagement::SceneManager::LoadFirstScene();
	}

	void GameEngine::LoadScene(const std::string& sceneName)
	{
		// 実際のシーン遷移はCheckAndChangeScene()で行う
		sceneNameToLoad = sceneName;
	}

	void GameEngine::CheckAndChangeScene()
	{
		if (sceneNameToLoad.empty()) {
			return;
		}

		SceneManagement::SceneManager::ChangeScene(sceneNameToLoad);
	}

	void GameEngine::RunGameLoop()
	{
		Time::Update();

		SceneManagement::Scene* activeScene = SceneManagement::SceneManager::GetActiveScene();
		if (activeScene) {
			activeScene->OnUpdate();
			activeScene->OnLateUpdate();
			activeScene->OnRender();
		}

		CheckAndChangeScene();
	}

#pragma region Windows プラットフォーム

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

	int GameEngine::StartWithWindows(HINSTANCE hInstance, int nCmdShow)
	{
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

