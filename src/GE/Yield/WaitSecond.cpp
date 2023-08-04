#include "WaitSecond.h"
#include "GE/Core/Time.h"

namespace GE::Yield
{
	WaitSecond::WaitSecond(float waitSecond) :
		waitSecond(waitSecond),
		startSecond(Time::GetTime())
	{
	}

	bool WaitSecond::operator()() const
	{
		return Time::GetTime() - startSecond >= waitSecond;
	}
}