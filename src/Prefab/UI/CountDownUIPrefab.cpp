#include "GE/GEHeader.h"
#include "CountDownUIPrefab.h"
#include "GE/UI/Text.h"
#include "Lang/LanguageManager.h"
#include "UI/CountDownUI.h"
#include "GE/Core/GEConfig.h"

namespace Prefab::UI
{
	::UI::CountDownUI& CountDownUIPrefab::operator()(GameObject& baseGameObject) const
	{
		baseGameObject.SetName("CountDownUI");

		auto& geConfig = GE::GetGEConfig();

		GameObject& textObj = baseGameObject.AddChild("Text");
		GE::UI::Text& text = textObj.AddComponent<GE::UI::Text>(Lang::LanguageManager::GetFont(Lang::FontType::DefaultLarge), Vector2Int(geConfig.screenWidth, geConfig.screenHeight));
		text.SetColor(Color::black);

		return baseGameObject.AddComponent<::UI::CountDownUI>(text);
	}
}
