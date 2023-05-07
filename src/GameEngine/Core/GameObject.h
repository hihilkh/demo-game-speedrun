#pragma once

#include "GameLoopBase.h"
#include "Render/RenderBase.h"
#include <vector>
#include <memory>
#include <functional>

namespace GE
{
	class Component;
	namespace Render
	{
		class Renderer;
	}
	namespace SceneManagement
	{
		class Scene;
	}

	class GameObject : public Internal::GameLoopBase, public Render::Internal::RenderBase
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
		std::vector<std::unique_ptr<Component>> nonRenderComponents;
		std::vector<std::unique_ptr<Render::Renderer>> renderers;
		std::vector<std::unique_ptr<GameObject>> children;

	private:
		/// <summary>
		/// 生成した後の最初の処理。有効無効にかかわらず呼び出される
		/// </summary>
		void OnAwake() override;
		/// <summary>
		/// Awake()段階の次の処理。有効無効にかかわらず呼び出される
		/// </summary>
		void OnStart() override;
		/// <summary>
		/// 毎フレームの処理。有効にする時のみ
		/// </summary>
		void OnUpdate() override;
		/// <summary>
		/// Update段階の次の処理。有効にする時のみ
		/// </summary>
		void OnLateUpdate() override;
		/// <summary>
		/// 描画の処理。有効にする時のみ
		/// </summary>
		void OnRender() override;

		void ExecuteByOrder(void (*func)(Internal::GameLoopBase&));
		void ExecuteRenderByOrder(void (*func)(Render::Internal::RenderBase&));
	};
}