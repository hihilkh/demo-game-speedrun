#pragma once

#include <string>
#include "GE/Debug/Log.h"

namespace GE::Tools
{
	struct ConstructorTest
	{
		std::string name;

		explicit ConstructorTest(const std::string& name) : name(name)
		{
			DEBUG_LOG(name << " : Constructor");
		}

		ConstructorTest(const ConstructorTest& other) : name(other.name)
		{
			DEBUG_LOG(name << " : Copy Constructor");
		}

		// otherのデストラクタもnameが読めるために、std::moveを使わない
		ConstructorTest(ConstructorTest&& other) noexcept : name(other.name)
		{
			DEBUG_LOG(name << " : Move Constructor");
		}

		void operator=(const ConstructorTest& other)
		{
			name = other.name;
			DEBUG_LOG(name << " : Copy assignment");
		}

		// otherのデストラクタもnameが読めるために、std::moveを使わない
		void operator=(ConstructorTest&& other) noexcept
		{
			name = other.name;
			DEBUG_LOG(name << " : Move assignment");
		}

		~ConstructorTest()
		{
			DEBUG_LOG(name << " : Destructor");
		}
	};
}