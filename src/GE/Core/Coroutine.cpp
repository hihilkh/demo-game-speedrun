#include "Coroutine.h"

namespace GE
{
	Coroutine::Coroutine(const std::function<bool()>& predicate, const std::function<void()>& func) :
		predicate(predicate),
		func(func)
	{
	}

	bool Coroutine::Update()
	{
		if (predicate()) {
			func();
			return true;
		}
		
		return false;
	}
}