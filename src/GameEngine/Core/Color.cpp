#include "Color.h"
#include "Utils/Math.h"

namespace GE
{
	const Color Color::black	(0.0f, 0.0f, 0.0f);
	const Color Color::white	(1.0f, 1.0f, 1.0f);
	const Color Color::red		(1.0f, 0.0f, 0.0f);
	const Color Color::green	(0.0f, 1.0f, 0.0f);
	const Color Color::blue		(0.0f, 0.0f, 1.0f);
	const Color Color::yellow	(1.0f, 1.0f, 0.0f);
	const Color Color::cyan		(0.0f, 1.0f, 1.0f);
	const Color Color::magenta	(1.0f, 0.0f, 1.0f);

	Color::Color() : Color(0.0f, 0.0f, 0.0f)
	{
	}

	Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
	{
	}

	Color Color::From8Bit(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
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
		return result += rhs;
	}

	Color operator-(const Color& lhs, const Color& rhs)
	{
		auto result = lhs;
		return result -= rhs;
	}

	Color operator*(const Color& lhs, const Color& rhs)
	{
		auto result = lhs;
		return result *= rhs;
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
}