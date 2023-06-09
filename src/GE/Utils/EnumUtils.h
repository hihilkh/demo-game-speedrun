#pragma once

#include <string>
#include <type_traits>
#include <magic_enum.hpp>

namespace GE::Enum
{
	template<typename E>
		requires std::is_enum_v<E>
	std::string ToString(E value)
	{
		return magic_enum::enum_name(value).data();
	}
}