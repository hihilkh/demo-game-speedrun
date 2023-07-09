#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include "TransformUtils/Direction.h"

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

		/// <param name="dirVector">長さは1とは限らない</param>
		void Move(const Vector2& dirVector);
		bool CanControl() const;

		TransformUtils::Direction GetDirection() const { return currentDir; }

	protected:
		void Awake() override;
		void PreDestroy() override;

	private:
		TransformUtils::Direction currentDir;

	private:
		void SceneReadyHandler(const Map::MapManager& mapManager);
	};
}
