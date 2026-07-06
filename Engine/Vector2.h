#pragma once

namespace bnhe {
	class Vector2 
	{
	public:
		float x, y;

		Vector2()                 : x{0}, y{0} {}
		Vector2(float v)          : x{v}, y{v} {}
		Vector2(float x, float y) : x{x}, y{y} {}

		/*Vector2 operator+=(Vector2 v) {
			x += v.x;
			y += v.y;
			return *this;
		}*/

		Vector2 operator+(Vector2 v) {
			x += v.x;
			y += v.y;
			return *this;
		}

		/*Vector2 operator-=(Vector2 v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}*/

		Vector2 operator-(Vector2 v) {
			x += v.x;
			y += v.y;
			return *this;
		}
	};
}