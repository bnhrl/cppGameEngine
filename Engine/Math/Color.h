#pragma once

#include <iostream>
#include <cassert>

namespace bnhe
{
	struct Color {
		Color(float a = 1.0f) : r{1.0f}, g{1.0f}, b{1.0f}, a{a} {}
		Color(float r, float g, float b, float a = 1.0f) : r{r}, g{g}, b{b}, a{a} {}
		float r, g, b, a;

		// Operators
		float operator [] (unsigned int i) const { assert(i < 4); return (&r)[i]; }
		float& operator [] (unsigned int i) { assert(i < 4); return (&r)[i]; }

		Color operator + (const Color& v) const { return Color(this->r + v.r, this->g + v.g, this->b + v.b); }
		Color operator - (const Color& v) const { return Color(this->r - v.r, this->g - v.g, this->b - v.b); }
		Color operator * (const Color& v) const { return Color(this->r * v.r, this->g * v.g, this->b * v.b); }
		Color operator / (const Color& v) const { return Color(this->r / v.r, this->g / v.g, this->b / v.b); }

		Color& operator += (const Color& v) { this->r += v.r; this->g += v.g; this->b += v.b; return *this; }
		Color& operator -= (const Color& v) { this->r -= v.r; this->g -= v.g; this->b -= v.b; return *this; }
		Color& operator *= (const Color& v) { this->r *= v.r; this->g *= v.g; this->b *= v.b; return *this; }
		Color& operator /= (const Color& v) { this->r /= v.r; this->g /= v.g; this->b /= v.b; return *this; }

		// Float operators

		Color operator + (const float v) const { return Color(this->r + v, this->g + v, this->b + v); }
		Color operator - (const float v) const { return Color(this->r - v, this->g - v, this->b - v); }
		Color operator * (const float v) const { return Color(this->r * v, this->g * v, this->b * v); }
		Color operator / (const float v) const { return Color(this->r / v, this->g / v, this->b / v); }

		Color operator += (const float v) { this->r += v; this->g += v; this->b += v; return *this; }
		Color operator -= (const float v) { this->r -= v; this->g -= v; this->b -= v; return *this; }
		Color operator *= (const float v) { this->r *= v; this->g *= v; this->b *= v; return *this; }
		Color operator /= (const float v) { this->r /= v; this->g /= v; this->b /= v; return *this; }

		Color ToUint8_T() {
			return { 
				static_cast<float>(r * 255), 
				static_cast<float>(g * 255),
				static_cast<float>(b * 255),
				static_cast<float>(a * 255)
			};
		}

		Color Lerp(Color target, float multiplier, float delta) const {
			Color temp = Color(this->r, this->g, this->b);
			float speed = std::exp(-multiplier * delta);
			temp.r = target.r + (temp.r - target.r) * speed;
			temp.g = target.g + (temp.g - target.g) * speed;
			temp.b = target.b + (temp.b - target.b) * speed;
			return temp;
		}
	};
}