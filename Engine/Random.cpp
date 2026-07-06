#include "pch.h"
#include "Random.h"

#include <cstdlib>

namespace bnhe
{
	int Random::m_resolution_x = 0;
	int Random::m_resolution_y = 0;

	void Random::SetResolution(int res_x, int res_y)
	{
		m_resolution_x = res_x;
		m_resolution_y = res_y;
	}

	int Random::Int(int max)
	{
		return rand() % (max + 1);
	}

	int Random::Int(int min, int max)
	{
		return Int(max - min) + min;
	}

	float Random::Float() {
		return rand() / (float)RAND_MAX;
	}

	float Random::Float(float max)
	{
		return Float() * max;
	}

	float Random::Float(float min, float max)
	{
		return min + Float() * (max - min);
	}

	int Random::PointOnScreenX()
	{
		return Int(m_resolution_x);
	}

	int Random::PointOnScreenY()
	{
		return Int(m_resolution_y);
	}
}