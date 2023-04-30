#include "GEHeader.h"
#include "DelayTrigger.h"

// TODO : 今スレッドセーフか
// TODO : MemberFunctionBaseを使わなくてもできるか <- 多分std::functionなどでもできる
namespace Time
{
	DelayTrigger::DelayTrigger(int waitTime, std::unique_ptr<MemberFunctionBase<>>&& func) :
		waitTime(waitTime),
		func(std::move(func)),
		startTime(std::chrono::steady_clock::now()),
		stopSource(std::stop_source())
	{
		std::jthread delayThread = std::jthread(&DelayTrigger::DelayAndTrigger, this, stopSource.get_token());
		delayThread.detach();
	}

	DelayTrigger::~DelayTrigger()
	{
		Cancel();
	}

	void DelayTrigger::DelayAndTrigger(std::stop_token stopToken)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

		if (!stopToken.stop_requested()) {
			(*this->func.get())();
		}
	}

	void DelayTrigger::Cancel() 
	{
		stopSource.request_stop();
	}
}