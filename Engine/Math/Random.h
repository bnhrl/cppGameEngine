#pragma once

#include <cstdlib>
#include <random>

#include "Math/Vector2.h"

namespace bnhe
{
	class Random
	{
	public:
		Random() = delete;

		inline static std::mt19937& Generator() {
			static std::random_device randomDevice;
			static std::mt19937 generator(randomDevice());
			
			return generator;
		}

		inline static void Seed(unsigned int seed) {
			Generator().seed(seed);
		}

		static void SetResolution(int res_x, int res_y);

		// Get random integer value; max is inclusive
		static int Int(int max);
		// Get random integer value; min and max are inclusive
		static int Int(int min, int max);
		static float Float();
		static float Float(float max);
		static float Float(float min, float max);
		static bool Bool();

		static int PointOnScreenX();
		static int PointOnScreenY();
		static Vector2 PointOnScreen();

	private:
		static int m_resolution_x;
		static int m_resolution_y;
	};
}

