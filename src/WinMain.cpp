#include <windows.h>

#include "Core/GameEngine.h"
#include "Core/Scene.h"

int WINAPI WinMain(
	_In_ HINSTANCE      hInstance,
	_In_opt_ HINSTANCE  hPrevInstance,
	_In_ LPSTR          lpCmdLine,
	_In_ int            nCmdShow
)
{
	// TODO : GE::Scene()
	int exitFlag = GE::GameEngine::Start(hInstance, nCmdShow, GE::Scene());
	return exitFlag;
}