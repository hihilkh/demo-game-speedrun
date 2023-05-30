#pragma once

#include <string>

namespace GE
{
	class GameObject;

	GameObject* FindGameObject(const std::string& name);
}