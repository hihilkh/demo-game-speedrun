#include "RectColliderVisual.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

#include "GE/Collision/RectCollider.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Transform2D.h"
#include "GE/Render/Image.h"
#include "ColliderVisualConfig.h"

#include "GE/Core/Component.h"

namespace GE::Debug::Collision
{
	namespace
	{
		const std::string gameObjectName = "RectColliderVisual";
		const std::string whiteImagePath = "./data/Image/White.png";

		class Control : public Component
		{
		public:
			Control(GameObject& gameObject, const RectCollider& collider, Image& image);
			virtual ~Control() = default;

		protected:
			const RectCollider& collider;
			Image& image;

		protected:
			void Update() override;
		};

#pragma region 関数定義

		Control::Control(GameObject& gameObject, const RectCollider& collider, Image& image) :
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
			GetTransform().SetPos(rect.Center());
			image.SetImageSize(rect.size);
		}

#pragma endregion
	}

	void AddRectColliderVisual(const RectCollider& collider)
	{
		GameObject& gameObject = collider.gameObject;

		auto& child = gameObject.AddChild(gameObjectName);
		auto& image = child.AddComponent<Image>(whiteImagePath);
		image.SetRenderPriority(colliderVisualRenderPriority);

		auto& control = child.AddComponent<Control>(collider, image);
	}
}

#endif