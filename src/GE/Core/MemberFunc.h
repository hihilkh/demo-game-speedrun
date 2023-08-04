﻿#pragma once

#include <type_traits>

namespace GE
{
    template<typename T>
    class MemberFuncBase;

    template<typename R, class... Args>
    class MemberFuncBase<R(Args...)>
    {
    public:
        virtual ~MemberFuncBase() = default;

        virtual R operator()(Args... args) const = 0;
    };

    /// <summary>
    /// インスタンスとメンバー関数によって等しいかどうかが判断できるクラス
    /// </summary>
    template<typename T, typename R, typename... Args>
    class MemberFunc final : public MemberFuncBase<R(Args...)>
    {
        using Func = std::conditional_t<std::is_const_v<T>, R(T::*)(Args...) const, R(T::*)(Args...)>;

    public:
        MemberFunc(Func func, T& instance);

        R operator()(Args... args) const override;

        template<typename T2, typename R2, typename... Args2>
        friend bool operator==(const MemberFunc<T2, R2, Args2...>& lhs, const MemberFunc<T2, R2, Args2...>& rhs);

    private:
        Func func;
        T& instance;
    };

    template<typename T, typename R, typename... Args, typename T2, typename R2, typename... Args2>
        requires (!std::is_same_v<MemberFunc<T, R, Args...>, MemberFunc<T2, R2, Args2...>>)
    bool operator==(const MemberFunc<T, R, Args...>& lhs, const MemberFunc<T2, R2, Args2...>& rhs)
    {
        return false;
    }

#pragma region テンプレート定義

    template<typename T, typename R, typename... Args>
    MemberFunc<T, R, Args...>::MemberFunc(Func func, T& instance) : func(func), instance(instance)
    {
    }

    template<typename T, typename R, typename... Args>
    R MemberFunc<T, R, Args...>::operator()(Args... args) const
    {
        return (instance.*func)(std::forward<Args>(args)...);
    }

    template<typename T, typename R, typename... Args>
    bool operator==(const MemberFunc<T, R, Args...>& lhs, const MemberFunc<T, R, Args...>& rhs)
    {
        if (&lhs.instance != &rhs.instance) {
            return false;
        }

        return lhs.func == rhs.func;
    }

#pragma endregion

#pragma region Deduction Guide
    template<typename T, typename R, typename... Args>
    MemberFunc(R(T::*)(Args...), T&) -> MemberFunc<T, R, Args...>;

    template<typename T, typename R, typename... Args>
    MemberFunc(R(T::*)(Args...) const, T&) -> MemberFunc<const T, R, Args...>;

    template<typename T, typename R, typename... Args>
    MemberFunc(R(T::*)(Args...) const, const T&) -> MemberFunc<const T, R, Args...>;

#pragma endregion
}