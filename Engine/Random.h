#pragma once

#include <cstdlib>

namespace bnhe
{
	class Random
	{
	public:
		Random() = delete;

		static void SetResolution(int res_x, int res_y);

		// Get random integer value; max is inclusive
		static int Int(int max);
		// Get random integer value; min and max are inclusive
		static int Int(int min, int max);
		static float Float();
		static float Float(float max);
		static float Float(float min, float max);

		static int PointOnScreenX();
		static int PointOnScreenY();

	private:
		static int m_resolution_x;
		static int m_resolution_y;
	};
}

