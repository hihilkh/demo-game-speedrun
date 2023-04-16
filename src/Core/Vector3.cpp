#include "Vector3.h"
#include <cmath>
#include "Vector2.h"

namespace GE
{

#pragma region Vector3

	const Vector3 Vector3::zero			( 0.0f,  0.0f,  0.0f);
	const Vector3 Vector3::one			( 1.0f,  1.0f,  1.0f);
	const Vector3 Vector3::up			( 0.0f,  1.0f,  0.0f);
	const Vector3 Vector3::down			( 0.0f, -1.0f,  0.0f);
	const Vector3 Vector3::left			( 1.0f,  0.0f,  0.0f);
	const Vector3 Vector3::right		(-1.0f,  0.0f,  0.0f);
	const Vector3 Vector3::forward		( 0.0f,  0.0f,  1.0f);
	const Vector3 Vector3::backward		( 0.0f,  0.0f, -1.0f);

	Vector3::Vector3() : Vector3(0.0f, 0.0f, 0.0f)
	{
	}

	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
	{
	}

	Vector3& Vector3::operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3& Vector3::operator*=(float multiple)
	{
		return Scale(multiple, multiple, multiple);
	}

	Vector3& Vector3::operator/=(float divisor)
	{
		x /= divisor;
		y /= divisor;
		z /= divisor;
		return *this;
	}

	Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
	{
		auto result = lhs;
		return result += rhs;
	}

	Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
	{
		auto result = lhs;
		return result -= rhs;
	}

	Vector3 operator*(const Vector3& vector, float multiple)
	{
		auto result = vector;
		return result *= multiple;
	}

	Vector3 operator*(float multiple, const Vector3& vector)
	{
		return vector * multiple;
	}

	Vector3 operator/(const Vector3& vector, float divisor)
	{
		auto result = vector;
		return result /= divisor;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	bool operator==(const Vector3& lhs, const Vector3& rhs)
	{
		return	lhs.x == rhs.x &&
				lhs.y == rhs.y &&
				lhs.z == rhs.z;
	}

	bool operator!=(const Vector3& lhs, const Vector3& rhs)
	{
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, const Vector3& vector)
	{
		return os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	}

	Vector3& Vector3::Scale(float multipleX, float multipleY, float multipleZ)
	{
		x *= multipleX;
		y *= multipleY;
		z *= multipleZ;
		return *this;
	}

	Vector3& Vector3::Scale(const Vector3& other)
	{
		return Scale(other.x, other.y, other.z);
	}

	Vector3 Vector3::Scale(const Vector3& lhs, const Vector3& rhs)
	{
		auto result = lhs;
		return result.Scale(rhs);
	}

	float Vector3::GetMagnitude() const
	{
		return sqrt(GetSqrMagnitude());
	}

	float Vector3::GetSqrMagnitude() const
	{
		return Dot(*this, *this);
	}

	float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
	{
		return	lhs.x * rhs.x +
				lhs.y * rhs.y +
				lhs.z * rhs.z;
	}

	float Vector3::Distance(const Vector3& lhs, const Vector3& rhs)
	{
		return (lhs - rhs).GetMagnitude();
	}

	Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(
			 lhs.y * rhs.z - lhs.z * rhs.y,
			-lhs.x * rhs.z + lhs.z * rhs.x,
			 lhs.x * rhs.y - lhs.y * rhs.x
		);
	}

	Vector3& Vector3::Normalize()
	{
		*this /= GetMagnitude();
		return *this;
	}

	Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
	{
		return Vector3(
			std::lerp(a.x, b.x, t),
			std::lerp(a.y, b.y, t),
			std::lerp(a.z, b.z, t)
		);
	}

	Vector3::operator Vector2() const
	{
		return Vector2(x, y);
	}

	Vector3::operator Vector2Int() const
	{
		return Vector2Int(static_cast<int>(x), static_cast<int>(y));
	}

	Vector3::operator Vector3Int() const
	{
		return Vector3Int(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z));
	}

#pragma endregion

#pragma region Vector3Int

	const Vector3Int Vector3Int::zero		( 0,  0,  0);
	const Vector3Int Vector3Int::one		( 1,  1,  1);
	const Vector3Int Vector3Int::up			( 0,  1,  0);
	const Vector3Int Vector3Int::down		( 0, -1,  0);
	const Vector3Int Vector3Int::left		( 1,  0,  0);
	const Vector3Int Vector3Int::right		(-1,  0,  0);
	const Vector3Int Vector3Int::forward	( 0,  0,  1);
	const Vector3Int Vector3Int::backward	( 0,  0, -1);

	Vector3Int::Vector3Int() : Vector3Int(0, 0, 0)
	{
	}

	Vector3Int::Vector3Int(int x, int y, int z) : x(x), y(y), z(z)
	{
	}

	Vector3Int& Vector3Int::operator+=(const Vector3Int& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3Int& Vector3Int::operator-=(const Vector3Int& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3Int& Vector3Int::operator*=(int multiple)
	{
		return Scale(multiple, multiple, multiple);
	}

	Vector3Int& Vector3Int::operator/=(int divisor)
	{
		x /= divisor;
		y /= divisor;
		z /= divisor;
		return *this;
	}

	Vector3Int operator+(const Vector3Int& lhs, const Vector3Int& rhs)
	{
		auto result = lhs;
		return result += rhs;
	}

	Vector3Int operator-(const Vector3Int& lhs, const Vector3Int& rhs)
	{
		auto result = lhs;
		return result -= rhs;
	}

	Vector3Int operator*(const Vector3Int& vector, int multiple)
	{
		auto result = vector;
		return result *= multiple;
	}

	Vector3Int operator*(int multiple, const Vector3Int& vector)
	{
		return vector * multiple;
	}

	Vector3Int operator/(const Vector3Int& vector, int divisor)
	{
		auto result = vector;
		return result /= divisor;
	}

	Vector3Int Vector3Int::operator-() const
	{
		return Vector3Int(-x, -y, -z);
	}

	bool operator==(const Vector3Int& lhs, const Vector3Int& rhs)
	{
		return	lhs.x == rhs.x &&
				lhs.y == rhs.y &&
				lhs.z == rhs.z;
	}

	bool operator!=(const Vector3Int& lhs, const Vector3Int& rhs)
	{
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, const Vector3Int& vector)
	{
		return os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	}

	Vector3Int& Vector3Int::Scale(int multipleX, int multipleY, int multipleZ)
	{
		x *= multipleX;
		y *= multipleY;
		z *= multipleZ;
		return *this;
	}

	Vector3Int& Vector3Int::Scale(const Vector3Int& other)
	{
		return Scale(other.x, other.y, other.z);
	}

	Vector3Int Vector3Int::Scale(const Vector3Int& lhs, const Vector3Int& rhs)
	{
		auto result = lhs;
		return result.Scale(rhs);
	}

	float Vector3Int::GetMagnitude() const
	{
		return static_cast<float>(sqrt(GetSqrMagnitude()));
	}

	int Vector3Int::GetSqrMagnitude() const
	{
		return	x * x + y * y + z * z;
	}

	float Vector3Int::Distance(const Vector3Int& lhs, const Vector3Int& rhs)
	{
		return (lhs - rhs).GetMagnitude();
	}

	Vector3Int::operator Vector2() const
	{
		return Vector2(static_cast<float>(x), static_cast<float>(y));
	}

	Vector3Int::operator Vector2Int() const
	{
		return Vector2Int(x, y);
	}

	Vector3Int::operator Vector3() const
	{
		return Vector3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
	}

#pragma endregion

}