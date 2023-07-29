#pragma once

namespace GE
{
	class GameObject;
}

namespace GE::Particle
{
	class Module
	{
	public:
		explicit Module() = default;
		virtual ~Module() = default;
		virtual void ApplyModule(GameObject& baseObject) = 0;
	};
}