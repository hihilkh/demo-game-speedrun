#pragma once

#include <concepts>

namespace GE
{
	class GameObject;
	class Component;
	namespace Particle
	{
		class Module;
	}

	template<typename T>
	concept VectorBaseType = std::is_same_v<int, T> || std::is_same_v<float, T>;

	template<typename T>
	concept RectBaseType = std::is_same_v<int, T> || std::is_same_v<float, T>;

	template<typename T>
	concept GameLoopObject = std::is_same_v<GameObject, T> || std::is_same_v<Component, T>;

	template<typename T>
	concept ComponentType = std::is_base_of_v<Component, T>;

	template<typename T>
	concept ParticleModuleType = std::is_base_of_v<Particle::Module, T>;
}
