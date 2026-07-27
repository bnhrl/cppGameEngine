#include "pch.h"
#include "framework.h"
#include "Engine.h"

#include <iostream>

namespace bnhe
{
	bool Engine::Initialize(int resolution_x, int resolution_y) {
		SetWorkingDirectory("Assets");
		std::cout << "Set working directory to " << GetWorkingDirectory() << "\n";
		m_input.Initialize();
		m_renderer.Initialize("Game Engine", resolution_x, resolution_y);
		m_audio.Initialize();
		Random::SetResolution(resolution_x, resolution_y);
		std::cout << "Engine initialized!" << "\n";
		return true;
	}

	void Engine::Shutdown() {
		m_input.Shutdown();
		m_renderer.Shutdown();
	}

	void Engine::Update() {
		m_input.Update();
		m_time.Tick();
	}

	void Engine::UpdateAudio() {
		m_audio.Update();
	}
}
