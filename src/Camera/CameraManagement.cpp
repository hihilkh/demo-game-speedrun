#include "GE/GEHeader.h"
#include "CameraManagement.h"

namespace Camera
{
	namespace
	{
		Camera2D* GetCamera(const std::string& cameraName)
		{
			GameObject* gameObject = GE::FindGameObject(cameraName);
			if (!gameObject) {
				return nullptr;
			}

			return gameObject->GetComponent<Camera2D>();
		}
	}

	Camera2D* GetMainCamera()
	{
		return GetCamera(mainCameraName);
	}

	Camera2D* GetUICamera()
	{
		return GetCamera(uiCameraName);
	}
}