#pragma once

#include <vector>
#include <memory>
#include "MemberFunction.tpp"

template<class OwnedClass, class... Args>
class Event {
	friend OwnedClass;

public:
	~Event() {}

private:
	typedef MemberFunctionBase<Args...> Listener;

	std::vector<std::unique_ptr<Listener>> listeners;

	void Invoke(Args... args)
	{
		for (auto& listener : listeners) {
			(*listener.get())(args...);
		}
	}

public:
	template<class T>
	void AddListener(T* instance, void(T::* func)(Args...))
	{
		listeners.push_back(std::make_unique<MemberFunction<T, Args...>>(instance, func));
	}

	// 備考：
	// 特定な listener を指定することは難しい。現段階は全部削除の関数しかない。
	/// <summary>
	/// instance によって全ての listeners を削除
	/// </summary>
	template<class T>
	void RemoveListeners(T* instance) {
		auto removeIt = std::remove_if(listeners.begin(), listeners.end(),
			[instance](auto& listener) { return listener->IsFuncOf(instance); });
		listeners.erase(removeIt, listeners.end());
	}
};