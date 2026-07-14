#pragma once

#include <iostream>

namespace bnhe
{
	struct Color {
		Color(float a = 1.0f) : r{1.0f}, g{1.0f}, b{1.0f}, a{a} {}
		Color(float r, float g, float b, float a = 255) : r{r}, g{g}, b{b}, a{a} {}
		float r, g, b, a;

		Color ToUint8_T() {
			return { 
				static_cast<float>(r * 255), 
				static_cast<float>(g * 255),
				static_cast<float>(b * 255),
				static_cast<float>(a * 255)
			};
		}
	};
}