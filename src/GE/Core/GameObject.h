#pragma once

#include "GameLoopBase.h"
#include "GE/Render/RenderBase.h"
#include <vector>
#include <memory>
#include <functional>
#include <type_traits>

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
		GameObject();	// ComponentとRendererが前方宣言できるために、コンストラクタを宣言し、cppで定義する
		~GameObject();	// ComponentとRendererが前方宣言できるために、デストラクタを宣言し、cppで定義する

		// TODO : Temp
		// parent
		// Set parent
		// GetEnable (global base)
		// Destroy
		// GetChild
		// GetComponent
		// Transform
		template<typename T>
		T& AddComponent(auto&&... args);

		static GameObject& CreateEmpty();

	private:
		std::vector<std::unique_ptr<Component>> nonRenderComponents;
		std::vector<std::unique_ptr<Render::Renderer>> renderers;
		std::vector<std::unique_ptr<GameObject>> children;

	private:

#pragma region ゲームループ

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

#pragma endregion

	};

#pragma region 関数テンプレート定義

	template<typename T>
	inline T& GameObject::AddComponent(auto&&... args)
	{
		static_assert(std::is_base_of_v<Component, T>, "The type must be a component");

		auto add = [&]() -> T& {
			if constexpr (std::is_base_of_v<Render::Renderer, T>) {
				auto& component = renderers.emplace_back(std::make_unique<T>(*this, args...));
				return static_cast<T&>(*component);
			} else {
				auto& component = nonRenderComponents.emplace_back(std::make_unique<T>(*this, args...));
				return static_cast<T&>(*component);
			}
		};

		T& component = add();
		component.OnAwake();
		component.OnStart();

		return component;
	}

#pragma endregion

}