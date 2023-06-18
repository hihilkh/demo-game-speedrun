#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include "GE/Core/Event.h"
#include "MapId.h"

namespace Map
{
	class MapManager : public Component
	{
	public:
		static GE::Event<> onMapLoaded;

	public:
		MapManager(GameObject& gameObject);

	protected:
		void Start() override;

	private:
		void LoadMap(const MapId& mapId, std::function<void()> onFinished = nullptr) const;
	};
}