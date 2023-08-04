#include "Coroutine.h"

namespace GE
{
	bool Coroutine::Update()
	{
		if (isMarkedDelete) {
			return true;
		}

		if (predicate()) {
			action();
			return true;
		}
		
		return false;
	}
}