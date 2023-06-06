#include "GE/GEHeader.h"
#include "MenuItem.h"
#include "GE/UI/Text.h"
#include "GE/Render/Image.h"

namespace UI
{
	MenuItem::MenuItem(GameObject& gameObject, GE::UI::Text& text, GE::Render::Image& arrowImage) :
		Component(gameObject),
		text(text),
		arrowImage(arrowImage),
		isSelecting(false)
	{
	}

	void MenuItem::Init(const std::string& text, bool isSelecting, std::function<void()> onClicked)
	{
		this->text.SetText(text);
		SetSelecting(isSelecting);
		this->onClicked = onClicked;
	}

	void MenuItem::Select()
	{
		SetSelecting(true);
	}

	void MenuItem::Unselect()
	{
		SetSelecting(false);
	}

	void MenuItem::SetSelecting(bool isSelecting)
	{
		this->isSelecting = isSelecting;
		arrowImage.SetEnable(isSelecting);
	}

	void MenuItem::Click() const
	{
		if (onClicked != nullptr) {
			onClicked();
		}
	}

}