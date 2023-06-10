#pragma once

namespace GE
{
	struct GEConfig;
	struct Color;
	class GameObject;

	namespace Internal
	{
		class Destroyable;
	}

	const GEConfig& GetGEConfig();
	void SetBGColor(const Color& color);

	void Destroy(GameObject& gameObject);
}