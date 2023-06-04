#pragma once

#include <functional>

namespace GE
{
	class Component;

	class Coroutine
	{
		friend Component;

	public:
		Coroutine(const Coroutine&) = delete;
		void operator=(const Coroutine&) = delete;

	private:

#pragma region Componentに呼び出される関数

		Coroutine(const std::function<bool()>& predicate, const std::function<void()>& func);

		/// <summary>
		/// 注意：Componentが無効になる時、Coroutine::Update()も呼び出さない。
		/// 参考：Component::OnUpdate()、GameObject::OnUpdate()
		/// </summary>
		bool Update();

#pragma endregion

	private:
		std::function<bool()> predicate;
		std::function<void()> func;

	};
}