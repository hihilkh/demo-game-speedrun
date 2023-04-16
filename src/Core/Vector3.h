#pragma once

#include <iostream>

// TODO : 
// Vector3はVector3Intよりいくつかのメンバー関数が持っている(e.g., Normalize())ので、クラステンプレートが使えない。
// 他のやり方を調べる

struct Vector2;
struct Vector2Int;
struct Vector3;
struct Vector3Int;

#pragma region Vector3

struct Vector3
{
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);

	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(float multiple);
	Vector3& operator/=(float divisor);

	friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator*(const Vector3& vector, float multiple);
	friend Vector3 operator*(float multiple, const Vector3& vector);
	friend Vector3 operator/(const Vector3& vector, float divisor);

	Vector3 operator-() const;

	friend bool operator==(const Vector3& lhs, const Vector3& rhs);
	friend bool operator!=(const Vector3& lhs, const Vector3& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Vector3& vector);

	Vector3& Scale(float multipleX, float multipleY, float multipleZ);
	Vector3& Scale(const Vector3& other);
	static Vector3 Scale(const Vector3& lhs, const Vector3& rhs);

	float GetMagnitude() const;
	float GetSqrMagnitude() const;

	static float Dot(const Vector3& lhs, const Vector3& rhs);
	static float Distance(const Vector3& lhs, const Vector3& rhs);
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

	Vector3& Normalize();
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	operator Vector2() const;
	operator Vector2Int() const;
	operator Vector3Int() const;

	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 left;
	static const Vector3 right;
	static const Vector3 forward;
	static const Vector3 backward;
};

#pragma endregion

#pragma region Vector3Int

struct Vector3Int
{
	int x, y, z;

	Vector3Int();
	Vector3Int(int x, int y, int z);

	Vector3Int& operator+=(const Vector3Int& other);
	Vector3Int& operator-=(const Vector3Int& other);
	Vector3Int& operator*=(int multiple);
	Vector3Int& operator/=(int divisor);

	friend Vector3Int operator+(const Vector3Int& lhs, const Vector3Int& rhs);
	friend Vector3Int operator-(const Vector3Int& lhs, const Vector3Int& rhs);
	friend Vector3Int operator*(const Vector3Int& vector, int multiple);
	friend Vector3Int operator*(int multiple, const Vector3Int& vector);
	friend Vector3Int operator/(const Vector3Int& vector, int divisor);

	Vector3Int operator-() const;

	friend bool operator==(const Vector3Int& lhs, const Vector3Int& rhs);
	friend bool operator!=(const Vector3Int& lhs, const Vector3Int& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Vector3Int& vector);

	Vector3Int& Scale(int multipleX, int multipleY, int multipleZ);
	Vector3Int& Scale(const Vector3Int& other);
	static Vector3Int Scale(const Vector3Int& lhs, const Vector3Int& rhs);

	float GetMagnitude() const;
	int GetSqrMagnitude() const;

	static float Distance(const Vector3Int& lhs, const Vector3Int& rhs);

	operator Vector2() const;
	operator Vector2Int() const;
	operator Vector3() const;

	static const Vector3Int zero;
	static const Vector3Int one;
	static const Vector3Int up;
	static const Vector3Int down;
	static const Vector3Int left;
	static const Vector3Int right;
	static const Vector3Int forward;
	static const Vector3Int backward;
};

#pragma endregion