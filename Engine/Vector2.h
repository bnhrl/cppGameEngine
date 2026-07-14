#pragma once

#include <cmath>
#include <cassert>

namespace bnhe {
	struct Vector2 
	{
		float x, y;

		Vector2()                 : x{0}, y{0} {}
		Vector2(float v)          : x{v}, y{v} {}
		Vector2(float x, float y) : x{x}, y{y} {}
		//Vector2(int x, int y)     : x{(float)x}, y{(float)y} {}


		// Vector operators

		float operator [] (unsigned int i) const { assert(i < 2); return (&x)[i]; }
		float& operator [] (unsigned int i) { assert(i < 2); return (&x)[i]; }

		bool operator == (const Vector2& v) { return this->x == v.x && this->y == v.y; }
		bool operator != (const Vector2& v) { return this->x != v.x && this->y != v.y; }


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
			float xDist = (float)std::pow(v.x - this->x, 2);
			float yDist = (float)std::pow(v.y - this->y, 2);
			return std::sqrt(xDist + yDist);
		}
		Vector2 Normalize() const { return (*this) / Length(); }
		Vector2 Lerp(Vector2 target, float multiplier, float delta) const {
			Vector2 temp = Vector2(this->x, this->y);
			float speed = std::exp(-multiplier * delta);
			temp.x = target.x + (temp.x - target.x) * speed;
			temp.y = target.y + (temp.y - target.y) * speed;
			return temp;
		}
		float Dot(const Vector2& v)          const { return (this->x * v.x) + (this->y * v.y); }
		float Angle()                        const { return std::atan2(this->x, this->y); }
		float AngleBetween(const Vector2& v) const { return std::acos(Dot(v)); }
		Vector2 Rotate(const Vector2& v, float radians) {
			float x = v.x * std::cos(radians) - v.y * std::sin(radians);
			float y = v.x * std::sin(radians) + v.y * std::cos(radians);

			return { x, y };
		}
	};
}