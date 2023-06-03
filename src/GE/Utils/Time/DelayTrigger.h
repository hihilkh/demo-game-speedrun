#pragma once

#include <chrono>
#include "Event/MemberFunction.tpp"
#include <thread>

// TODO : GE namespace に合わせる
namespace Time
{
	class DelayTrigger
	{
	private:
		DelayTrigger(const DelayTrigger&) = delete;
		DelayTrigger& operator=(const DelayTrigger&) = delete;

	public:
		/// <param name="waitTime">ミリ秒</param>
		DelayTrigger(int waitTime, std::unique_ptr<MemberFunctionBase<>>&& func);
		~DelayTrigger();

	private:
		int waitTime;
		std::unique_ptr<MemberFunctionBase<>> func;
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::stop_source stopSource;

	private:
		void DelayAndTrigger(std::stop_token st);

	public:
		void Cancel();
	};
}