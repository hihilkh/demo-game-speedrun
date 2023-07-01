#include "GE/GEHeader.h"
#include <windows.h>

#include "GE/Core/GameEngine.h"
#include "GE/MainProgram/MainProgramInitParams.h"
#include "Scene/SceneMapping.h"
#include "Common/CollisionInfo.h"
#include "GE/Collision/CollisionLayerMatrix.h"

int WINAPI WinMain(
	_In_ HINSTANCE      hInstance,
	_In_opt_ HINSTANCE  hPrevInstance,
	_In_ LPSTR          lpCmdLine,
	_In_ int            nCmdShow
)
{
	GE::GameEngine::SetSceneConfig(Scene::CreateSceneConfig());
	GE::GameEngine::SetCollisionLayerMatrix(CollisionInfo::CreateCollisionLayerMatrix());
	int exitFlag = GE::GameEngine::Start({ hInstance, nCmdShow });
	return exitFlag;
}