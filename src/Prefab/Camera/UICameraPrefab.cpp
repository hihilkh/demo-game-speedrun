#include "GE/GEHeader.h"
#include "UICameraPrefab.h"
#include "Camera/CameraManagement.h"

namespace Prefab::Camera
{
	Camera2D& UICameraPrefab::operator()(GameObject& baseGameObject) const
	{
		baseGameObject.SetName(::Camera::uiCameraName);
		Camera2D& uiCamera = baseGameObject.AddComponent<Camera2D>();
		uiCamera.SetCullingMask(RenderLayer::ui);
		uiCamera.SetPriority(10);

		return uiCamera;
	}
}
