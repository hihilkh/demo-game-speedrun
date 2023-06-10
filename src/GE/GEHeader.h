﻿#pragma once

// プリコンパイル済みヘッダー(Precompiled Header File)

#include <string>
#include <functional>
#include <algorithm>
#include <memory>
#include <iostream>
#include <type_traits>
#include <cmath>
#include <tuple>
#include <cassert>

// コンテナー
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

// ゲームエンジン
#include "DataType/Vector2.h"
#include "DataType/Vector3.h"
#include "DataType/Color.h"

#include "Debug/Log.h"

#include "Core/GameObject.h"
#include "Core/Component.h"
#include "Core/Time.h"
#include "Core/Transform2D.h"
#include "Core/Camera2D.h"
#include "Core/Prefab.h"
#include "Core/Event.h"

#include "Core/Coroutine.h"
#include "Yield/headers.h"

#include "Render/RenderLayer.h"

#include "Utils/HandyFunc/GameEngineRelated.h"
#include "Utils/HandyFunc/SceneRelated.h"
#include "Utils/TypeDef.h"

