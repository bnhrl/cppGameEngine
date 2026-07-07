#include "pch.h"
#include "Input.h"

#include <SDL3/SDL.h>

namespace bnhe
{
	bool Input::Initialize()
	{
		int numKeys;
		const bool* keyState = SDL_GetKeyboardState(&numKeys);
		
		m_keyStates.resize(numKeys);
		std::copy(keyState, keyState + numKeys, m_keyStates.begin());
		m_prevKeyStates = m_keyStates;



		return true;
	}

	void Input::Shutdown()
	{
		// bleghhhhh
	}


	void Input::Update()
	{
		m_prevKeyStates = m_keyStates;
		int numKeys;
		const bool* keyState = SDL_GetKeyboardState(&numKeys);
		if (numKeys != m_keyStates.size()) {
			m_keyStates.resize(numKeys);
		}
		std::copy(keyState, keyState + m_keyStates.size(), m_keyStates.begin());

		SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
	}
}