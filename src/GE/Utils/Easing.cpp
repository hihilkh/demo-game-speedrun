#include "Easing.h"
#include "Math.h"
#include <cassert>
#include <magic_enum.hpp>
#include <string>

namespace GE::Easing
{
	namespace
	{
		inline float EaseInOutSine(float t)
		{
			return -(std::cos((float)std::numbers::pi * t) - 1.0f) / 2.0f;
		}
	}

	float Ease(float t, Type type)
	{
		switch (type) {
			case Type::InOutSine:	return EaseInOutSine(t);
		}

		assert(false && (std::string("Ease Type : ") + magic_enum::enum_name(type).data() + "のEase関数はまだ実装していない").c_str());

		// 警告を出さないように
		return 0.0f;
	}

	float BoundedEase(float t, Type type)
	{
		return Ease(Math::Clamp01(t), type);
	}
}