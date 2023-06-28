﻿#pragma once

#include "PrefabDeclaration.h"
#include "GameObject.h"

namespace GE
{
#pragma region 関数テンプレート定義

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab, GameObject* parent)
	{
		GameObject* baseGameObject = parent;
		if (baseGameObject == nullptr) {
			baseGameObject = &GameObject::CreateWithDelayAwake();
		}

		PrefabReturnType<PrefabT> returnValue = prefab(*baseGameObject);
		baseGameObject->AwakeIfSceneLoaded();

		return returnValue;
	}

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab, Scene& scene)
	{
		GameObject& baseGameObject = GameObject::CreateWithDelayAwake(scene);
		PrefabReturnType<PrefabT> returnValue = prefab(baseGameObject);
		baseGameObject.AwakeIfSceneLoaded();

		return returnValue;
	}

	/// <summary>
	/// PrefabをPersistent Sceneの中で生成する。つまり、sceneを遷移する際にも破棄されない。
	/// </summary>
	template<typename PrefabT>
	PrefabReturnType<PrefabT> InstantiatePersistent(PrefabT prefab, GameObject* parent)
	{
		GameObject* baseGameObject = parent;
		if (baseGameObject == nullptr) {
			baseGameObject = &GameObject::CreatePersistentWithDelayAwake();
		}

		PrefabReturnType<PrefabT> returnValue = prefab(*baseGameObject);
		baseGameObject->AwakeIfSceneLoaded();

		return returnValue;
	}

#pragma endregion

}