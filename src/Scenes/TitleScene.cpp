#include "GE/GEHeader.h"
#include "TitleScene.h"
#include "GE/SceneManagement/Scene.h"
#include "GE/Render/Image.h"
#include "GE/Tools/ConstructorTest.h"

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
			DEBUG_LOG("Update");
		}
		void LateUpdate() override
		{
			DEBUG_LOG("LateUpdate");
		}
	};
	std::unique_ptr<GE::SceneManagement::Scene> TitleScene::operator()() const
	{
		auto scene = std::make_unique<GE::SceneManagement::Scene>(titleSceneName);
		GameObject& a = scene->AddGameObject();

		a.AddComponent<Test>(GE::Tools::ConstructorTest("Hello"), GE::Tools::ConstructorTest("Bye"));
		a.AddComponent<GE::Render::Image>("./data/Image/Title.png", RectPixel(0, 0, 300, 50));

		return scene;
	}
}