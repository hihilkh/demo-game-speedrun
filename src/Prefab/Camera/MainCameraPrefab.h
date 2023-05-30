#pragma once

namespace GE
{
	class GameObject;
	class Camera2D;
}

namespace Prefab::Camera
{
	class MainCameraPrefab
	{
	public:
		GE::Camera2D& operator()(GE::GameObject& baseGameObject) const;
	};
}