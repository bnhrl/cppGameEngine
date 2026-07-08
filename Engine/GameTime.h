#pragma once

#include <cstdint>

namespace bnhe{
	class Time 
	{
	public:
		Time();

		void Reset();
		void Tick();

		float GetTime()      { return TicksToSeconds(m_currentTicks); }
		float GetDeltaTime() { return TicksToSeconds(m_deltaTicks); }

		float TicksToSeconds(uint64_t ticks) { return (float)ticks / 1'000'000'000; }

	private:
		uint64_t m_startTicks = 0;
		uint64_t m_currentTicks = 0;
		uint64_t m_frameTicks = 0;
		uint64_t m_deltaTicks = 0;
	};
}