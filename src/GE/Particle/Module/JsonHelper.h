#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Utils/Json.h"

namespace GE::Particle::JsonHelper
{
	Rect ConvertToRect(const GE::Json::Value& json);
	Color ConvertToColor(const GE::Json::Value& json);
	Vector2 ConvertToRange(const GE::Json::Value& json);
	Vector2 ConvertToVector2(const GE::Json::Value& json);
}