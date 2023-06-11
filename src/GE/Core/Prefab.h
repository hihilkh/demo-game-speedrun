#pragma once

#include "PrefabDeclaration.h"
#include "GameObject.h"

namespace GE
{
#pragma region 関数テンプレート定義

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab)
	{
		GameObject& baseGameObject = GameObject::CreateWithDelayInit();
		PrefabReturnType<PrefabT> returnValue = prefab(baseGameObject);
		baseGameObject.InitIfSceneLoaded();

		return returnValue;
	}

	template<typename PrefabT>
	PrefabReturnType<PrefabT> Instantiate(PrefabT prefab, Scene& scene)
	{
		GameObject& baseGameObject = GameObject::CreateWithDelayInit(scene);
		PrefabReturnType<PrefabT> returnValue = prefab(baseGameObject);
		baseGameObject.InitIfSceneLoaded();

		return returnValue;
	}

	/// <summary>
	/// PrefabをPersistent Sceneの中で生成する。つまり、sceneを遷移する際にも破棄されない。
	/// </summary>
	template<typename PrefabT>
	PrefabReturnType<PrefabT> InstantiatePersistent(PrefabT prefab)
	{
		GameObject& baseGameObject = GameObject::CreatePersistentWithDelayInit();
		PrefabReturnType<PrefabT> returnValue = prefab(baseGameObject);
		baseGameObject.InitIfSceneLoaded();

		return returnValue;
	}

#pragma endregion

}