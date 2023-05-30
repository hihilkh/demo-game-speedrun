#include "GE/GEHeader.h"
#include "MainCameraPrefab.h"
#include "Camera/CameraManagement.h"

namespace Prefab::Camera
{
	Camera2D& MainCameraPrefab::operator()(GameObject& baseGameObject) const
	{
		baseGameObject.SetName(::Camera::mainCameraName);
		Camera2D& mainCamera = baseGameObject.AddComponent<Camera2D>();
		mainCamera.SetCullingMask(RenderLayer::nonUI);
		mainCamera.SetPriority(0);

		return mainCamera;
	}
}
