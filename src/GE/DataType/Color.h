#pragma once

#include <iostream>
#include <cstdint>

namespace GE
{
	struct Color
	{
		float r, g, b, a;

		Color();
		Color(float r, float g, float b, float a = 1.0f);

		static Color From8Bit(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0, std::uint8_t a = 255);

		Color& operator+=(const Color& other);
		Color& operator-=(const Color& other);
		Color& operator*=(const Color& other);

		friend Color operator+(const Color& lhs, const Color& rhs);
		friend Color operator-(const Color& lhs, const Color& rhs);
		friend Color operator*(const Color& lhs, const Color& rhs);

		friend bool operator==(const Color& lhs, const Color& rhs);
		friend bool operator!=(const Color& lhs, const Color& rhs);

		friend std::ostream& operator<<(std::ostream& os, const Color& color);

		Color& Clamp01();

		static Color Lerp(const Color& a, const Color& b, float t);

		static const Color black;
		static const Color white;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color yellow;
		static const Color cyan;
		static const Color magenta;
	};
}