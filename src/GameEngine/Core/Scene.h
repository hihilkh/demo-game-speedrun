#pragma once

#include <string>
#include "Debug/Log.h"

namespace GE
{
	class Scene
	{
		friend class GameEngine;

	public:
		Scene()
		{
			DEBUG_LOG("Construct");
		}

		Scene(const std::string& name)
		{
			DEBUG_LOG("Construct : " << name);
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

	public:
		const std::string& GetName() const { return name; }

	private:
		std::string name;

	private:
		void Init();
		void Update();
		void LateUpdate();
		void Render();
	};
}