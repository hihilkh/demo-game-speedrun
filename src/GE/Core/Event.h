#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <algorithm>
#include "MemberFunc.h"

namespace GE
{
	// TODO : GE::Event<>をGE::Eventで表すことができるか

	template<typename... Args>
	class Event
	{
	public:

		void Invoke(Args... args);

		/// <summary>
		/// 一般的な関数をAddListenerした後、指定的に除くこと(RemoveListener)ができない。
		/// </summary>
		template<typename F>
		void AddListener(F&& func);

		template<typename T>
		void AddListener(void (T::*func)(Args...), T& instance);

		template<typename T>
		void AddListener(void (T::* func)(Args...) const, const T& instance);

		template<typename T>
		void RemoveListener(void (T::* func)(Args...), T& instance);

		template<typename T>
		void RemoveListener(void (T::* func)(Args...) const, const T& instance);

		void RemoveAllListeners();

	private:
		std::vector<std::function<void(Args...)>> nonMemberFuncListeners;
		std::vector<std::unique_ptr<MemberFuncBase<void(Args...)>>> memberFuncListeners;

	private:
		template<typename T>
		void RemoveListener(const MemberFunc<T, void, Args...>& memberFunc);
	};

#pragma region テンプレート定義

	template<typename... Args>
	void Event<Args...>::Invoke(Args... args)
	{
		for (auto& listener : nonMemberFuncListeners) {
			listener(std::forward<Args>(args)...);
		}

		for (auto& listener : memberFuncListeners) {
			(*listener.get())(std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	template<typename F>
	void Event<Args...>::AddListener(F&& func)
	{
		nonMemberFuncListeners.emplace_back(std::forward<F>(func));
	}

	template<typename... Args>
	template<typename T>
	void Event<Args...>::AddListener(void (T::*func)(Args...), T& instance)
	{
		memberFuncListeners.push_back(std::make_unique<MemberFunc<T, void, Args...>>(func, instance));
	}

	template<typename... Args>
	template<typename T>
	void Event<Args...>::AddListener(void (T::* func)(Args...) const, const T& instance)
	{
		memberFuncListeners.push_back(std::make_unique<MemberFunc<const T, void, Args...>>(func, instance));
	}

	template<typename... Args>
	template<typename T>
	void Event<Args...>::RemoveListener(void (T::* func)(Args...), T& instance)
	{
		RemoveListener(MemberFunc(func, instance));
	}

	template<typename... Args>
	template<typename T>
	void Event<Args...>::RemoveListener(void (T::* func)(Args...) const, const T& instance)
	{
		RemoveListener(MemberFunc(func, instance));
	}

	template<typename... Args>
	template<typename T>
	void Event<Args...>::RemoveListener(const MemberFunc<T, void, Args...>& memberFunc)
	{
		using DerivedType = MemberFunc<T, void, Args...>;

		auto removeAlgorithm = [&memberFunc](auto& listener) -> bool {
			DerivedType* casted = dynamic_cast<DerivedType*>(listener.get());
			if (casted) {
				return *casted == memberFunc;
			}

			return false;
		};

		auto removeIt = std::remove_if(
			memberFuncListeners.begin(), 
			memberFuncListeners.end(),
			removeAlgorithm);
		memberFuncListeners.erase(removeIt, memberFuncListeners.end());
	}

	template<typename... Args>
	void Event<Args...>::RemoveAllListeners()
	{
		nonMemberFuncListeners.clear();
		memberFuncListeners.clear();
	}

#pragma endregion
}