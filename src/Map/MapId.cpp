#include "GE/GEHeader.h"
#include "MapId.h"

namespace Map
{
	MapId::MapId(const char* id) : value(id)
	{
	}

	MapId::MapId(const std::string& id) : value(id)
	{
	}

	std::string MapId::GetFilePath() const
	{
		return "./data/Map/" + value + ".txt";
	}
}