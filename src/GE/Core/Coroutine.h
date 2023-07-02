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

		template<typename Predicate, typename Action>
		Coroutine(Predicate&& predicate, Action&& action) :
			predicate(std::forward<Predicate>(predicate)),
			action(std::forward<Action>(action)),
			isMarkedDelete(false)
		{
		}

		/// <summary>
		/// <para>注意：Componentが無効になる時、Coroutine::Update()も呼び出さない。</para>
		/// <para>参考：Component::OnUpdate()、GameObject::OnUpdate()</para>
		/// </summary>
		/// <returns>
		/// <para>仕事もう終わるかどうか。すなわち、</para>
		/// <para>- actionが呼び出された、または</para>
		/// <para>- isMarkedDelete = true</para>
		/// </returns>
		bool Update();

#pragma endregion

	private:
		std::function<bool()> predicate;
		std::function<void()> action;

		bool isMarkedDelete;
	};
}