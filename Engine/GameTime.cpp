#include "pch.h"
#include "GameTime.h"

#include <SDL3//SDL.h>

namespace bnhe 
{
	Time::Time()
	{
		m_startTicks = SDL_GetTicksNS();
		m_frameTicks = SDL_GetTicksNS();
		m_currentTicks = SDL_GetTicksNS();
	}
	void Time::Reset()
	{

	}

	void Time::Tick()
	{
		m_currentTicks = SDL_GetTicksNS();
		m_deltaTicks = m_currentTicks - m_frameTicks;
		m_frameTicks = m_currentTicks;
	}
}
