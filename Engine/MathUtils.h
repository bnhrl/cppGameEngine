#pragma once


namespace bnhe::math
{
	const float PI = 3.1415927f;
	const float PI_TWO = PI*2;

	template<typename T>
	T Min(T a, T b) {
		return (a < b) ? a : b;
	}
	
	template<typename T>
	T Max(T a, T b) {
		return (a > b) ? a : b;
	}

	template<typename T>
	T Wrap(T value, T min, T max) {
		if (value > max) value = min;
		if (value < min) value = max;
		return value;
	}

	template<typename T>
	T Clamp(T value, T min, T max) {
		return (value < min) ? min : 
			   (value > max) ? max : 
			   value;
	}
}