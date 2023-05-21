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
		GameObject& mainCameraObject = GameObject::Create("MainCamera", *scene);
		auto& camera = mainCameraObject.AddComponent<Camera2D>();

		GameObject& a = GameObject::Create("a", *scene);
		GameObject& b = a.CreateChild("b");

		//a.AddComponent<Test>(GE::Tools::ConstructorTest("Hello"), GE::Tools::ConstructorTest("Bye"));
		a.GetTransform().pos = { 0.0f, 0.0f };
		a.GetTransform().rot = 0;
		auto& imageA = a.AddComponent<GE::Render::Image>("./data/Image/Title.png");
		imageA.SetScale({ 0.5f, 1.0f });
		b.GetTransform().pos = { 0.0f, 0.0f };
		b.GetTransform().rot = 20;
		auto& imageB = b.AddComponent<GE::Render::Image>("./data/Image/Chara01.png");
		imageB.SetScale({ 2.0f, 2.0f });
		imageB.SetRenderPriority(-1);

		GE::Render::Image* image = a.GetComponent<GE::Render::Image>();
		Test* test = a.GetComponent<Test>();

		GameObject* bPtr = scene->FindGameObject("b");
		GameObject* cPtr = scene->FindGameObject("c");

		return scene;
	}
}