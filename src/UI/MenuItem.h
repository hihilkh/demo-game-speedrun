#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include <string>

namespace GE
{
	namespace UI
	{
		class Text;
	}

	namespace Render
	{
		class Image;
	}
}

namespace UI
{
	class MenuItem : public Component
	{
	public:
		MenuItem(GameObject& gameObject, GE::UI::Text& text, GE::Render::Image& arrowImage);

	public:
		void Init(const std::string& text, bool isSelecting, std::function<void()> onClicked);
		void Select();
		void Unselect();
		void Click() const;

	private:
		GE::UI::Text& text;
		GE::Render::Image& arrowImage;

		bool isSelecting;

		std::function<void()> onClicked;

	private:
		void SetSelecting(bool isSelecting);
	};
}