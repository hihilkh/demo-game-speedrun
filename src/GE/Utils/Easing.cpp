#include "Easing.h"
#include "Math.h"
#include <cassert>
#include <string>

namespace GE::Easing
{
	namespace
	{
		inline float EaseLinear(float t)
		{
			return t;
		}

		inline float EaseInOutSine(float t)
		{
			return -(std::cos((float)std::numbers::pi * t) - 1.0f) / 2.0f;
		}
	}

	float Ease(float t, Type type)
	{
		switch (type) {
			case Type::Linear:		return EaseLinear(t);
			case Type::InOutSine:	return EaseInOutSine(t);
		}

		assert(false && "該当するEasing::TypeはまだEase関数の中で実装していない");

		// 警告を出さないように
		return 0.0f;
	}

	float BoundedEase(float t, Type type)
	{
		return Ease(Math::Clamp01(t), type);
	}
}