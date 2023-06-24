#include "RectColliderVisual.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

#include "GE/Physics/RectCollider.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Transform2D.h"
#include "GE/Render/Image.h"
#include "ColliderVisualConfig.h"

#include "GE/Core/Component.h"

namespace GE::Debug::Physics
{
	namespace
	{
		const std::string gameObjectName = "RectColliderVisual";
		const std::string whiteImagePath = "./data/Image/White.png";

		class Control : public Component
		{
		protected:
			const GE::Physics::RectCollider& collider;
			GE::Render::Image& image;

		public:
			Control(GameObject& gameObject, const GE::Physics::RectCollider& collider, GE::Render::Image& image);
			virtual ~Control() = default;

		protected:
			void Update() override;
		};

#pragma region 関数定義

		Control::Control(GameObject& gameObject, const GE::Physics::RectCollider& collider, GE::Render::Image& image) :
			Component(gameObject),
			collider(collider),
			image(image)
		{
		}

		void Control::Update()
		{
			image.SetIsEnable(collider.GetIsEnable());
			if (!image.GetIsEnable()) {
				return;
			}

			image.SetColor(collider.GetIsTrigger() ? triggerColor : colliderColor);

			const Rect& rect = collider.GetRect();
			GetTransform().pos = rect.Center();
			image.SetImageSize(rect.size);
		}

#pragma endregion
	}

	void AddRectColliderVisual(const GE::Physics::RectCollider& collider)
	{
		GameObject& gameObject = collider.gameObject;

		auto& child = gameObject.AddChild(gameObjectName);
		auto& image = child.AddComponent<GE::Render::Image>(whiteImagePath);
		image.SetRenderPriority(colliderVisualRenderPriority);

		auto& control = child.AddComponent<Control>(collider, image);
	}
}

#endif