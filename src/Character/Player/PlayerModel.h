#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"

namespace Map
{
	class MapManager;
}

namespace Player
{
	class PlayerModel : public Component
	{
	public:
		explicit PlayerModel(GameObject& gameObject);

	public:
		void Move(const Vector2& direction, float speed);

	protected:
		void Awake() override;
		void PreDestroy() override;

	private:
		void SceneReadyHandler(const Map::MapManager& mapManager);
	};
}
