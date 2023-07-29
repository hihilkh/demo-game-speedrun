#pragma once

#include "GEConcept.h"
#include <stdint.h>

#pragma region 前方宣言

namespace GE
{
	class GameObject;
	class Component;
	class Transform2D;
	class Camera2D;
	struct Color;
	class Time;

	namespace DataType::Internal
	{
		template<VectorBaseType T>
		struct TVector2;
		template<VectorBaseType T>
		struct TVector3;

		template<RectBaseType T>
		struct TRect;
	}

	namespace Render
	{
		class Image;

		namespace RenderLayer
		{
		}
	}

	namespace Collision
	{
		class Collider;
		class RectCollider;

		namespace Detection
		{
			enum class CollidedType : std::uint8_t;
		}

		namespace CollisionLayer
		{
		}
	}

	namespace Animation
	{
		class Animator;
	}

	namespace Particle
	{
		class ParticleSystem;
	}
}

#pragma endregion

#pragma region typedef

using GameObject		= GE::GameObject;
using Component			= GE::Component;
using Transform2D		= GE::Transform2D;
using Camera2D			= GE::Camera2D;
using Color				= GE::Color;
using Time				= GE::Time;

using Vector2			= GE::DataType::Internal::TVector2<float>;
using Vector2Int		= GE::DataType::Internal::TVector2<int>;
using Vector3			= GE::DataType::Internal::TVector3<float>;
using Vector3Int		= GE::DataType::Internal::TVector3<int>;

using Image				= GE::Render::Image;
namespace RenderLayer	= GE::Render::RenderLayer;

using Collider				= GE::Collision::Collider;
using RectCollider			= GE::Collision::RectCollider;
using CollidedType			= GE::Collision::Detection::CollidedType;
namespace CollisionLayer	= GE::Collision::CollisionLayer;

using Animator				= GE::Animation::Animator;

using ParticleSystem		= GE::Particle::ParticleSystem;

// 備考：
// 本質的に TRect<float> と TRect<int> は大きな違いがある。
// TRect<float> の場合、点はサイズがない。
// TRect<int> の場合、点が 1 x 1 のサイズとみなす。
// (参考：TRect::FromMinMax())
// そういうわけで、TRect<int> を RectInt ではなく、RectPixel と命名する。

using Rect			= GE::DataType::Internal::TRect<float>;
using RectPixel		= GE::DataType::Internal::TRect<int>;

#pragma endregion