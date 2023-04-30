#pragma once

#include "Debug/Log.h"
namespace GE
{
	class Scene
	{
	public:
		Scene()
		{
			DEBUG_LOG("Construct");
		}

		Scene(const Scene& other)
		{
			DEBUG_LOG("Copy");
		}

		Scene(Scene&& other) noexcept
		{
			DEBUG_LOG("Move");
		}

		~Scene()
		{
			DEBUG_LOG("destroy");
		}
	};
}