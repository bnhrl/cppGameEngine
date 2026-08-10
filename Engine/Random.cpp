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
		std::uniform_int_distribution<> dist(0, max - 1);
		return dist(Generator());
	}

	int Random::Int(int min, int max)
	{
		if (min > max) std::swap(min, max);

		std::uniform_int_distribution<> dist(min, max - 1);
		return dist(Generator());
	}

	float Random::Float() {
		static std::uniform_real_distribution<float> dist(0.f, 1.f);
		return dist(Generator());
	}

	float Random::Float(float max)
	{
		std::uniform_real_distribution<float> dist(0.f, max);
		return dist(Generator());
	}

	float Random::Float(float min, float max)
	{
		if (min > max) std::swap(min, max);

		std::uniform_real_distribution<float> dist(min, max);
		return dist(Generator());
	}

	bool Random::Bool() {
		std::bernoulli_distribution dist(0.5f);
		return dist(Generator());
	}

	int Random::PointOnScreenX()
	{
		return Int(m_resolution_x);
	}

	int Random::PointOnScreenY()
	{
		return Int(m_resolution_y);
	}

	Vector2 Random::PointOnScreen() {
		return Vector2((float)Random::PointOnScreenX(), (float)Random::PointOnScreenY());
	}
}