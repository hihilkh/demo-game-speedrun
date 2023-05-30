#include "GE/GEHeader.h"
#include "TitleScene.h"
#include "GE/SceneManagement/Scene.h"
#include "GE/Render/Image.h"
#include "GE/Tools/ConstructorTest.h"
#include "GE/Input/InputSystem.h"
#include "GE/UI/Text.h"
#include "Lang/LanguageManager.h"

namespace Scene
{
	class Test : public Component
	{
	public:
		GE::Tools::ConstructorTest a;

		Test(GameObject& gameObject) : Component(gameObject), a("Test")
		{

		}

		Test(GameObject& gameObject, const GE::Tools::ConstructorTest& a, const GE::Tools::ConstructorTest& b) : Component(gameObject), a(a)
		{

		}

		void Awake() override
		{
			DEBUG_LOG("Test Awake");
		}

		void Start() override
		{
			DEBUG_LOG("Test Start");
		}

		void Update() override
		{
			//DEBUG_LOG("Update");
			if (GE::Input::GetKeyDown(GE::Input::Key::a)) {
				DEBUG_LOG("Key down");
			}

			if (GE::Input::GetKeyOn(GE::Input::Key::a)) {
				DEBUG_LOG("Key on");
			}

			if (GE::Input::GetKeyUp(GE::Input::Key::a)) {
				DEBUG_LOG("Key up");
			}
		}
		void LateUpdate() override
		{
			//DEBUG_LOG("LateUpdate");
		}
	};
	std::unique_ptr<GE::SceneManagement::Scene> TitleScene::operator()() const
	{
		auto scene = std::make_unique<GE::SceneManagement::Scene>(titleSceneName);
		GameObject& mainCameraObject = GameObject::Create("MainCamera", *scene);
		auto& camera = mainCameraObject.AddComponent<Camera2D>();
		camera.SetCullingMask(RenderLayer::nonUI);

		GameObject& uiCameraObject = GameObject::Create("UICamera", *scene);
		auto& uiCamera = uiCameraObject.AddComponent<Camera2D>();
		uiCamera.SetCullingMask(RenderLayer::ui);
		uiCamera.SetPriority(1);

		GameObject& a = GameObject::Create("a", *scene);
		GameObject& b = a.CreateChild("b");

		//a.GetTransform().pos = { 0.0f, 0.0f };
		//a.GetTransform().rot = 0;
		//auto& imageA = a.AddComponent<GE::Render::Image>("./data/Image/Title.png");
		//imageA.SetScale({ 0.5f, 1.0f });
		//b.GetTransform().pos = { 0.0f, 0.0f };
		//b.GetTransform().rot = 20;
		//auto& imageB = b.AddComponent<GE::Render::Image>("./data/Image/Chara01.png");
		//imageB.SetScale({ 2.0f, 2.0f });
		//imageB.SetRenderPriority(-1);

		GameObject& ui = GameObject::Create("ui", *scene);
		ui.GetTransform().pos.x = -300;
		auto& text = ui.AddComponent<GE::UI::Text>(Lang::LanguageManager::GetFont(Lang::FontType::DefaultSmall), Vector2Int(100, 100));
		text.SetText("hi");

		GameObject& ui2 = GameObject::Create("ui2", *scene);
		ui2.GetTransform().pos.x = 300;
		auto& text2 = ui2.AddComponent<GE::UI::Text>(Lang::LanguageManager::GetFont(Lang::FontType::DefaultSmall), Vector2Int(100, 100));
		text2.SetText("あいう");

		GameObject& ui3 = GameObject::Create("ui3", *scene);
		auto& bgImage = ui3.AddComponent<GE::Render::Image>("./data/Image/White.png");
		bgImage.SetColor(Color::red);
		bgImage.SetImageSize({ 400.0f, 400.0f });
		auto& text3 = ui3.AddComponent<GE::UI::Text>(Lang::LanguageManager::GetFont(Lang::FontType::DefaultLarge), Vector2Int(400, 400));
		text3.SetText("私君\nあいう\nYou and me");
		text3.SetVerticalAlignment(GE::UI::TextVerticalAlignment::Bottom);
		text3.SetHorizontalAlignment(GE::UI::TextHorizontalAlignment::Right);

		return scene;
	}
}