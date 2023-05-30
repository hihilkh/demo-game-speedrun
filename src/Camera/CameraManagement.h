#pragma once

#include <string>

namespace GE
{
	class Camera2D;
}

namespace Camera
{
	inline const std::string mainCameraName = "MainCamera";
	inline const std::string uiCameraName = "UICamera";

	GE::Camera2D* GetMainCamera();
	GE::Camera2D* GetUICamera();
}