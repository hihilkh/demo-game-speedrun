#pragma once

#include <functional>
#include <utility>

namespace GE
{
	class GameObject;
	class Scene;

	template<typename T>
	using Prefab = std::function<T(GameObject& baseGameObject)>;

	template<typename PrefabT>
	using PrefabReturnType = decltype(std::declval<PrefabT>()(std::declval<GameObject&>()));

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab);

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab, Scene& scene);
}