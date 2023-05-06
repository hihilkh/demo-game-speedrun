#pragma once

#include "GameLoopObject.h"

// TODO : Temp
namespace GE
{
	class Component : public Internal::GameLoopObject
	{
		// TODO : Temp
		// isActive (global base)

	public:
		// GameObjectが無効になる前に、必ず持っているComponentを破棄する
		//class GameObject& gameObject;

	public:
		virtual ~Component() = default;
	};
}