#include "GE/GEHeader.h"
#include "MenuItemPrefab.h"
#include "GE/UI/Text.h"
#include "Lang/LanguageManager.h"

namespace Prefab
{
	void MenuItemPrefab::operator()(GameObject& baseGameObject) const
	{
		baseGameObject.SetName("MenuItem");
		baseGameObject.GetTransform().pos.x = -300;
		auto& text = baseGameObject.AddComponent<GE::UI::Text>(Lang::LanguageManager::GetFont(Lang::FontType::DefaultSmall), Vector2Int(100, 100));
		text.SetText("hi");
	}
}
