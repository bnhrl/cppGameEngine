#pragma once

#include <iostream>

namespace bnhe
{
	class Color {
	public:
		Color(uint8_t a = 255) : r{255}, g{255}, b{255}, a{a} {}
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r{r}, g{g}, b{b}, a{a} {}
		uint8_t r, g, b, a;
	};
}