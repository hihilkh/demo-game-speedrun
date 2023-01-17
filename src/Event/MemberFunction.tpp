#pragma once

template<class... FuncArgs>
class MemberFunctionBase {
protected:
	virtual void* GetInstancePtr() const = 0;

public:
	virtual ~MemberFunctionBase() {}
	virtual void operator()(FuncArgs... args) = 0;

	bool IsFuncOf(void* instance)
	{
		return GetInstancePtr() == instance;
	}
};

/// <summary>
/// 注意：このクラスはダングリングポインタのチェックがない
/// </summary>
template<class T, class... FuncArgs>
class MemberFunction final : public MemberFunctionBase<FuncArgs...> {

	typedef void (T::*Func)(FuncArgs...);

private:
	T* instance;
	Func func;

protected:
	void* GetInstancePtr() const override { return static_cast<void*>(instance); }

public:
	MemberFunction(T* instance, Func func) : instance(instance), func(func)
	{
	}

	void operator()(FuncArgs... args) override
	{
		(instance->*func)(args...);
	}
};