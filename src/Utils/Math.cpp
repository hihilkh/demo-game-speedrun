#include "Math.h"
#include <cmath>

namespace Math
{
	int FloorDivide(int dividend, int divisor)
	{
		return (int)floor(float(dividend) / divisor);
	}
}