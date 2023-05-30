#pragma once

namespace GE
{
	class GameObject;
	class Camera2D;
}

namespace Prefab::Camera
{
	class UICameraPrefab
	{
	public:
		GE::Camera2D& operator()(GE::GameObject& baseGameObject) const;
	};
}