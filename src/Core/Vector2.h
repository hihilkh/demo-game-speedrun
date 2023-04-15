#pragma once

#include <iostream>

// TODO : 
// Vector2はVector2Intよりいくつかのメンバー関数が持っている(e.g., Normalize())ので、クラステンプレートが使えない。
// 他のやり方を調べる

struct Vector2;
struct Vector2Int;
struct Vector3;
struct Vector3Int;

#pragma region Vector2

struct Vector2
{
	float x, y;

	Vector2();
	Vector2(float x, float y);

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(float multiple);
	Vector2& operator/=(float divisor);

	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator*(const Vector2& vector, float multiple);
	friend Vector2 operator*(float multiple, const Vector2& vector);
	friend Vector2 operator/(const Vector2& vector, float divisor);

	Vector2 operator-() const;

	friend bool operator==(const Vector2& lhs, const Vector2& rhs);
	friend bool operator!=(const Vector2& lhs, const Vector2& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);

	void Scale(float multipleX, float multipleY);
	void Scale(const Vector2& other);
	static Vector2 Scale(const Vector2& lhs, const Vector2& rhs);

	float GetMagnitude() const;
	float GetSqrMagnitude() const;

	static float Dot(const Vector2& lhs, const Vector2& rhs);
	static float Distance(const Vector2& lhs, const Vector2& rhs);

	void Normalize();
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

	operator Vector2Int() const;
	operator Vector3() const;
	operator Vector3Int() const;

	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 up;
	static const Vector2 down;
	static const Vector2 left;
	static const Vector2 right;
};

#pragma endregion

#pragma region Vector2Int

struct Vector2Int
{
	int x, y;

	Vector2Int();
	Vector2Int(int x, int y);

	Vector2Int& operator+=(const Vector2Int& other);
	Vector2Int& operator-=(const Vector2Int& other);
	Vector2Int& operator*=(int multiple);
	Vector2Int& operator/=(int divisor);

	friend Vector2Int operator+(const Vector2Int& lhs, const Vector2Int& rhs);
	friend Vector2Int operator-(const Vector2Int& lhs, const Vector2Int& rhs);
	friend Vector2Int operator*(const Vector2Int& vector, int multiple);
	friend Vector2Int operator*(int multiple, const Vector2Int& vector);
	friend Vector2Int operator/(const Vector2Int& vector, int divisor);

	Vector2Int operator-() const;

	friend bool operator==(const Vector2Int& lhs, const Vector2Int& rhs);
	friend bool operator!=(const Vector2Int& lhs, const Vector2Int& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Vector2Int& vector);

	void Scale(int multipleX, int multipleY);
	void Scale(const Vector2Int& other);
	static Vector2Int Scale(const Vector2Int& lhs, const Vector2Int& rhs);

	float GetMagnitude() const;
	int GetSqrMagnitude() const;

	static float Distance(const Vector2Int& lhs, const Vector2Int& rhs);

	operator Vector2() const;
	operator Vector3() const;
	operator Vector3Int() const;

	static const Vector2Int zero;
	static const Vector2Int one;
	static const Vector2Int up;
	static const Vector2Int down;
	static const Vector2Int left;
	static const Vector2Int right;
};

#pragma endregion