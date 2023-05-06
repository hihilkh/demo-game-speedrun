#pragma once

#include "GameLoopObject.h"
#include <vector>
#include <memory>
#include <functional>

namespace GE
{
	namespace SceneManagement
	{
		class Scene;
	}

	class GameObject : public Internal::GameLoopObject
	{
		friend SceneManagement::Scene;

	public:
		~GameObject();	// ComponentとRendererが前方宣言できるために、デストラクタを宣言し、cppで定義する
		// TODO : Temp
		// parent
		// GetEnable (global base)
		// Instantiate to current scene
		// Destroy
		// GetChild
		// AddComponent
		// RemoveComponent
		// GetComponent
		// Transform

	private:
		std::vector<std::unique_ptr<class Component>> nonRenderComponents;
		std::vector<std::unique_ptr<class Renderer>> renderers;
		std::vector<std::unique_ptr<GameObject>> children;

	private:
		/// <summary>
		/// 生成した後の最初の処理。GetEnable()にかかわらず呼び出される
		/// </summary>
		void Awake() override;
		/// <summary>
		/// Awake()段階の次の処理。GetEnable()にかかわらず呼び出される
		/// </summary>
		void Start() override;
		/// <summary>
		/// 毎フレームの処理。GetEnable() == trueの時のみ
		/// </summary>
		void Update() override;
		/// <summary>
		/// Update段階の次の処理。GetEnable() == trueの時のみ
		/// </summary>
		void LateUpdate() override;
		/// <summary>
		/// 描画の処理。GetEnable() == trueの時のみ
		/// </summary>
		void Render();

		void ExecuteByOrder(void (*func)(Internal::GameLoopObject&));
	};
}