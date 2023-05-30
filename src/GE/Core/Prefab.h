#pragma once

#include "GameObject.h"
#include <functional>
#include <utility>

namespace GE
{
	template<typename T>
	using Prefab = std::function<T(GameObject& baseGameObject)>;

	template<typename PrefabT>
	using PrefabReturnType = decltype(std::declval<PrefabT>()(std::declval<GameObject&>()));

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab);

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab, Scene::Scene& scene);

#pragma region 関数テンプレート定義

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab)
	{
		GameObject& baseGameObject = GameObject::Create();
		return prefab(baseGameObject);
	}

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab, Scene::Scene& scene)
	{
		GameObject& baseGameObject = GameObject::Create(scene);
		return prefab(baseGameObject);
	}

#pragma endregion

}