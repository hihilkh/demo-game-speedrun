﻿#include "GEHeader.h"
#include <windows.h>

#include "Core/GameEngine.h"
#include "MainProgram/MainProgramInitParams.h"
#include "Scenes/SceneMapping.h"

int WINAPI WinMain(
	_In_ HINSTANCE      hInstance,
	_In_opt_ HINSTANCE  hPrevInstance,
	_In_ LPSTR          lpCmdLine,
	_In_ int            nCmdShow
)
{
	GE::GameEngine::SetSceneConfig(Scene::CreateSceneConfig());
	int exitFlag = GE::GameEngine::Start({ hInstance, nCmdShow });
	return exitFlag;
}