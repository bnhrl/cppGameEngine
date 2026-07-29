#include "pch.h"
#include "Engine.h"

#include "framework.h"

#include <iostream>

namespace bnhe
{
	bool Engine::Initialize(int resolution_x, int resolution_y) {
		SetWorkingDirectory("Assets");
		std::cout << "Set working directory to " << GetWorkingDirectory() << "\n";
		m_input.Initialize();
		m_renderer.Initialize("Game Engine", resolution_x, resolution_y);
		m_audio.Initialize();
		m_particle_system.Initialize(5000);
		Random::SetResolution(resolution_x, resolution_y);
		std::cout << "Engine initialized!" << "\n";
		return true;
	}

	void Engine::Shutdown() {
		m_input.Shutdown();
		m_renderer.Shutdown();
		m_particle_system.Shutdown();
	}

	void Engine::Update() {
		m_input.Update();
		m_time.Tick();
		m_particle_system.Update(m_time.GetDeltaTime());
	}

	void Engine::UpdateAudio() {
		m_audio.Update();
	}
}
