#pragma once

#include <cmath>

namespace bnhe {
	class Vector2 
	{
	public:
		float x, y;

		Vector2()                 : x{0}, y{0} {}
		Vector2(float v)          : x{v}, y{v} {}
		Vector2(float x, float y) : x{x}, y{y} {}
		//Vector2(int x, int y)     : x{(float)x}, y{(float)y} {}


		// Vector operators

		Vector2 operator + (const Vector2& v) const { return Vector2(this->x + v.x, this->y + v.y); }
		Vector2 operator - (const Vector2& v) const { return Vector2(this->x - v.x, this->y - v.y); }
		Vector2 operator * (const Vector2& v) const { return Vector2(this->x * v.x, this->y * v.y); }
		Vector2 operator / (const Vector2& v) const { return Vector2(this->x / v.x, this->y / v.y); }

		Vector2& operator += (const Vector2& v) { this->x += v.x; this->y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { this->x -= v.x; this->y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { this->x *= v.x; this->y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { this->x /= v.x; this->y /= v.y; return *this; }

		// Float operators

		Vector2 operator + (const float v) const { return Vector2(this->x + v, this->y + v); }
		Vector2 operator - (const float v) const { return Vector2(this->x - v, this->y - v); }
		Vector2 operator * (const float v) const { return Vector2(this->x * v, this->y * v); }
		Vector2 operator / (const float v) const { return Vector2(this->x / v, this->y / v); }

		Vector2 operator += (const float v) { this->x += v; this->y += v; return *this; }
		Vector2 operator -= (const float v) { this->x -= v; this->y -= v; return *this; }
		Vector2 operator *= (const float v) { this->x *= v; this->y *= v; return *this; }
		Vector2 operator /= (const float v) { this->x /= v; this->y /= v; return *this; }

		// Methods

		float LengthSqr() const { return (x * x) + (y * y); }
		float Length()    const { return std::sqrt(LengthSqr()); }
		float DistanceTo(const Vector2 v) const
		{
			float xDist = std::pow(v.x - this->x, 2);
			float yDist = std::pow(v.y - this->y, 2);
			return std::sqrt(xDist + yDist);
		}
	};
}