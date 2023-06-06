﻿#include "GE/GEHeader.h"
#include "MenuItemPrefab.h"
#include "GE/UI/Text.h"
#include "Lang/LanguageManager.h"
#include "GE/Render/Image.h"
#include "UI/MenuItem.h"

namespace Prefab::UI
{
	::UI::MenuItem& MenuItemPrefab::operator()(GameObject& baseGameObject) const
	{
		baseGameObject.SetName("MenuItem");

		GameObject& textObj = baseGameObject.AddChild("Text");
		GE::UI::Text& text = textObj.AddComponent<GE::UI::Text>(Lang::LanguageManager::GetFont(Lang::FontType::DefaultSmall), Vector2Int(350, 100));
		text.SetColor(Color::white);

		GameObject& arrowObj = baseGameObject.AddChild("Arrow");
		auto& arrowImage = arrowObj.AddComponent<GE::Render::Image>("./data/Image/Arrow.png");
		arrowImage.SetRenderLayer(RenderLayer::ui);
		arrowImage.SetColor(Color::green);
		
		// textの左側 (ちょっと隙間が入っている (arrowImageのsizeの半分))
		arrowObj.GetTransform().pos.x = -(text.GetLabelSize().x / 2.0f + arrowImage.GetImageSize().x);

		return baseGameObject.AddComponent<::UI::MenuItem>(text, arrowImage);
	}
}
