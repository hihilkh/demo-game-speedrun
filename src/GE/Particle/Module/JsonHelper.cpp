#include "JsonHelper.h"
#include "GE/DataType/Rect.h"
#include "GE/DataType/Color.h"
#include "GE/DataType/Vector2.h"

namespace GE::Particle::JsonHelper
{
	namespace
	{
		const std::string xNode = "x";
		const std::string yNode = "y";
		const std::string wideNode = "w";
		const std::string heightNode = "h";

		const std::string rNode = "r";
		const std::string gNode = "g";
		const std::string bNode = "b";
		const std::string aNode = "a";

		const std::string fromNode = "from";
		const std::string toNode = "to";
	}

	Rect ConvertToRect(const GE::Json::Value& json)
	{
		return Rect(
			json[xNode].asFloat(),
			json[yNode].asFloat(),
			json[wideNode].asFloat(),
			json[heightNode].asFloat()
		);
	}

	Color ConvertToColor(const GE::Json::Value& json)
	{
		return Color(
			json[rNode].asFloat(),
			json[gNode].asFloat(),
			json[bNode].asFloat(),
			json[aNode].asFloat()
		);
	}

	Vector2 ConvertToRange(const GE::Json::Value& json)
	{
		return Vector2(
			json[fromNode].asFloat(),
			json[toNode].asFloat()
		);
	}

	Vector2 ConvertToVector2(const GE::Json::Value& json)
	{
		return Vector2(
			json[xNode].asFloat(),
			json[yNode].asFloat()
		);
	}
}