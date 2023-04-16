#include "Vector2.h"
#include <cmath>
#include "Vector3.h"

namespace GE
{

#pragma region Vector2

	const Vector2 Vector2::zero(0.0f, 0.0f);
	const Vector2 Vector2::one(1.0f, 1.0f);
	const Vector2 Vector2::up(0.0f, 1.0f);
	const Vector2 Vector2::down(0.0f, -1.0f);
	const Vector2 Vector2::left(-1.0f, 0.0f);
	const Vector2 Vector2::right(1.0f, 0.0f);

	Vector2::Vector2() : Vector2(0.0f, 0.0f)
	{
	}

	Vector2::Vector2(float x, float y) : x(x), y(y)
	{
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& Vector2::operator*=(float multiple)
	{
		return Scale(multiple, multiple);
	}

	Vector2& Vector2::operator/=(float divisor)
	{
		x /= divisor;
		y /= divisor;
		return *this;
	}

	Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		auto result = lhs;
		return result += rhs;
	}

	Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
	{
		auto result = lhs;
		return result -= rhs;
	}

	Vector2 operator*(const Vector2& vector, float multiple)
	{
		auto result = vector;
		return result *= multiple;
	}

	Vector2 operator*(float multiple, const Vector2& vector)
	{
		return vector * multiple;
	}

	Vector2 operator/(const Vector2& vector, float divisor)
	{
		auto result = vector;
		return result /= divisor;
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-x, -y);
	}

	bool operator==(const Vector2& lhs, const Vector2& rhs)
	{
		return	lhs.x == rhs.x &&
			lhs.y == rhs.y;
	}

	bool operator!=(const Vector2& lhs, const Vector2& rhs)
	{
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, const Vector2& vector)
	{
		return os << "(" << vector.x << ", " << vector.y << ")";
	}

	Vector2& Vector2::Scale(float multipleX, float multipleY)
	{
		x *= multipleX;
		y *= multipleY;
		return *this;
	}

	Vector2& Vector2::Scale(const Vector2& other)
	{
		return Scale(other.x, other.y);
	}

	Vector2 Vector2::Scale(const Vector2& lhs, const Vector2& rhs)
	{
		auto result = lhs;
		return result.Scale(rhs);
	}

	float Vector2::GetMagnitude() const
	{
		return sqrt(GetSqrMagnitude());
	}

	float Vector2::GetSqrMagnitude() const
	{
		return Dot(*this, *this);
	}

	float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
	{
		return	lhs.x * rhs.x +
			lhs.y * rhs.y;
	}

	float Vector2::Distance(const Vector2& lhs, const Vector2& rhs)
	{
		return (lhs - rhs).GetMagnitude();
	}

	Vector2& Vector2::Normalize()
	{
		*this /= GetMagnitude();
		return *this;
	}

	Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
	{
		return Vector2(
			std::lerp(a.x, b.x, t),
			std::lerp(a.y, b.y, t)
		);
	}

	Vector2::operator Vector2Int() const
	{
		return Vector2Int(static_cast<int>(x), static_cast<int>(y));
	}

	Vector2::operator Vector3() const
	{
		return Vector3(x, y, 0.0f);
	}

	Vector2::operator Vector3Int() const
	{
		return Vector3Int(static_cast<int>(x), static_cast<int>(y), 0);
	}

#pragma endregion

#pragma region Vector2Int

	const Vector2Int Vector2Int::zero(0, 0);
	const Vector2Int Vector2Int::one(1, 1);
	const Vector2Int Vector2Int::up(0, 1);
	const Vector2Int Vector2Int::down(0, -1);
	const Vector2Int Vector2Int::left(-1, 0);
	const Vector2Int Vector2Int::right(1, 0);

	Vector2Int::Vector2Int() : Vector2Int(0, 0)
	{
	}

	Vector2Int::Vector2Int(int x, int y) : x(x), y(y)
	{
	}

	Vector2Int& Vector2Int::operator+=(const Vector2Int& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2Int& Vector2Int::operator-=(const Vector2Int& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2Int& Vector2Int::operator*=(int multiple)
	{
		return Scale(multiple, multiple);
	}

	Vector2Int& Vector2Int::operator/=(int divisor)
	{
		x /= divisor;
		y /= divisor;
		return *this;
	}

	Vector2Int operator+(const Vector2Int& lhs, const Vector2Int& rhs)
	{
		auto result = lhs;
		return result += rhs;
	}

	Vector2Int operator-(const Vector2Int& lhs, const Vector2Int& rhs)
	{
		auto result = lhs;
		return result -= rhs;
	}

	Vector2Int operator*(const Vector2Int& vector, int multiple)
	{
		auto result = vector;
		return result *= multiple;
	}

	Vector2Int operator*(int multiple, const Vector2Int& vector)
	{
		return vector * multiple;
	}

	Vector2Int operator/(const Vector2Int& vector, int divisor)
	{
		auto result = vector;
		return result /= divisor;
	}

	Vector2Int Vector2Int::operator-() const
	{
		return Vector2Int(-x, -y);
	}

	bool operator==(const Vector2Int& lhs, const Vector2Int& rhs)
	{
		return	lhs.x == rhs.x &&
			lhs.y == rhs.y;
	}

	bool operator!=(const Vector2Int& lhs, const Vector2Int& rhs)
	{
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, const Vector2Int& vector)
	{
		return os << "(" << vector.x << ", " << vector.y << ")";
	}

	Vector2Int& Vector2Int::Scale(int multipleX, int multipleY)
	{
		x *= multipleX;
		y *= multipleY;
		return *this;
	}

	Vector2Int& Vector2Int::Scale(const Vector2Int& other)
	{
		return Scale(other.x, other.y);
	}

	Vector2Int Vector2Int::Scale(const Vector2Int& lhs, const Vector2Int& rhs)
	{
		auto result = lhs;
		return result.Scale(rhs);
	}

	float Vector2Int::GetMagnitude() const
	{
		return static_cast<float>(sqrt(GetSqrMagnitude()));
	}

	int Vector2Int::GetSqrMagnitude() const
	{
		return x * x + y * y;
	}

	float Vector2Int::Distance(const Vector2Int& lhs, const Vector2Int& rhs)
	{
		return (lhs - rhs).GetMagnitude();
	}

	Vector2Int::operator Vector2() const
	{
		return Vector2(static_cast<float>(x), static_cast<float>(y));
	}

	Vector2Int::operator Vector3() const
	{
		return Vector3(static_cast<float>(x), static_cast<float>(y), 0.0f);
	}

	Vector2Int::operator Vector3Int() const
	{
		return Vector3Int(x, y, 0);
	}

#pragma endregion

}