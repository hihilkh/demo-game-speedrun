#pragma once

#include "GameLoopObject.h"

// TODO : Temp
namespace GE
{
	class Renderer : public Internal::GameLoopObject
	{
		friend class GameObject;

	public:
		virtual ~Renderer() = default;

	protected:
		virtual void Render() {}
	};
}