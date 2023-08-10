#include "Color.h"
#include "GE/Utils/Math.h"

namespace GE
{
	Color::Color() : Color(1.0f, 1.0f, 1.0f)
	{
	}

	Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
	{
	}

	Color Color::From8Bit(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
	{
		return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}

	Color& Color::operator+=(const Color& other)
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		return *this;
	}

	Color& Color::operator-=(const Color& other)
	{
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;
		return *this;
	}

	Color& Color::operator*=(const Color& other)
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;
		return *this;
	}

	Color operator+(const Color& lhs, const Color& rhs)
	{
		auto result = lhs;
		result += rhs;		// Return Value Optimization (RVO)のために、直接的に "return result += rhs;" をしない
		return result;
	}

	Color operator-(const Color& lhs, const Color& rhs)
	{
		auto result = lhs;
		result -= rhs;
		return result;
	}

	Color operator*(const Color& lhs, const Color& rhs)
	{
		auto result = lhs;
		result *= rhs;
		return result;
	}

	bool operator==(const Color& lhs, const Color& rhs)
	{
		return	lhs.r == rhs.r &&
				lhs.g == rhs.g &&
				lhs.b == rhs.b &&
				lhs.a == rhs.a;
	}

	bool operator!=(const Color& lhs, const Color& rhs)
	{
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, const Color& color)
	{
		return os << "(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
	}

	Color& Color::Clamp01()
	{
		r = Math::Clamp01(r);
		g = Math::Clamp01(g);
		b = Math::Clamp01(b);
		a = Math::Clamp01(a);
		return *this;
	}

	Color Color::Lerp(const Color& a, const Color& b, float t)
	{
		return Color(
			std::lerp(a.r, b.r, t),
			std::lerp(a.g, b.g, t),
			std::lerp(a.b, b.b, t),
			std::lerp(a.a, b.a, t)
		);
	}
}