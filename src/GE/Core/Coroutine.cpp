#include "Coroutine.h"

namespace GE
{
	bool Coroutine::Update()
	{
		if (predicate()) {
			action();
			return true;
		}
		
		return false;
	}
}