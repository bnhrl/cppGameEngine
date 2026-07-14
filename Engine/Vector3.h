#pragma once

#include <cmath>
#include <cassert>

namespace bnhe {
	struct Vector3
	{
		float x, y, z;

		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
		Vector3(float v) : x{ v }, y{ v }, z{ v } {}
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}


		// Vector operators

		float operator [] (unsigned int i) const { assert(i < 3); return (&x)[i]; }
		float& operator [] (unsigned int i) { assert(i < 3); return (&x)[i]; }

		bool operator == (const Vector3& v) { return this->x == v.x && this->y == v.y && this->z == v.z; }
		bool operator != (const Vector3& v) { return this->x != v.x && this->y != v.y && this->z != v.z; }


		Vector3 operator + (const Vector3& v) const { return Vector3(this->x + v.x, this->y + v.y, this->z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(this->x - v.x, this->y - v.y, this->z - v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(this->x * v.x, this->y * v.y, this->z * v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(this->x / v.x, this->y / v.y, this->z / v.z); }

		Vector3& operator += (const Vector3& v) { this->x += v.x; this->y += v.y; this->z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { this->x *= v.x; this->y *= v.y; this->z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { this->x /= v.x; this->y /= v.y; this->z /= v.z; return *this; }

		// Float operators

		Vector3 operator + (const float v) const { return Vector3(this->x + v, this->y + v, this->z + v); }
		Vector3 operator - (const float v) const { return Vector3(this->x - v, this->y - v, this->z - v); }
		Vector3 operator * (const float v) const { return Vector3(this->x * v, this->y * v, this->z * v); }
		Vector3 operator / (const float v) const { return Vector3(this->x / v, this->y / v, this->z / v); }

		Vector3 operator += (const float v) { this->x += v; this->y += v; this->z += v; return *this; }
		Vector3 operator -= (const float v) { this->x -= v; this->y -= v; this->z -= v; return *this; }
		Vector3 operator *= (const float v) { this->x *= v; this->y *= v; this->z *= v; return *this; }
		Vector3 operator /= (const float v) { this->x /= v; this->y /= v; this->z /= v; return *this; }

		// Methods

		float LengthSqr() const { return (x * x) + (y * y); }
		float Length()    const { return std::sqrt(LengthSqr()); }
		float DistanceTo(const Vector3 v) const
		{
			float xDist = (float)std::pow(v.x - this->x, 2);
			float yDist = (float)std::pow(v.y - this->y, 2);
			float zDist = (float)std::pow(v.z - this->z, 2);
			return std::sqrt(xDist + yDist + zDist);
		}
		Vector3 Normalize() const { return (*this) / Length(); }
		Vector3 Lerp(Vector3 target, float multiplier, float delta) const {
			Vector3 temp = Vector3(this->x, this->y, this->z);
			float speed = std::exp(-multiplier * delta);
			temp.x = target.x + (temp.x - target.x) * speed;
			temp.y = target.y + (temp.y - target.y) * speed;
			return temp;
		}
	};
}