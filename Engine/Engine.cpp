#include "pch.h"
#include "Engine.h"

#include "Components/SpriteRendererComponent.h"
#include "Components/SpriteAnimationRendererComponent.h"
#include "Components/CircleColliderComponent.h"

namespace bnhe
{
	bool Engine::Initialize(int resolution_x, int resolution_y) {
		std::cout << "Set working directory to " << GetWorkingDirectory() << "\n";

		//// Register static library
		//Factory::Instance().Register<SpriteRendererComponent>("SpriteRendererComponent");
		//Factory::Instance().Register<SpriteAnimationRendererComponent>("SpriteAnimationRendererComponent");
		//Factory::Instance().Register<CircleColliderComponent>("CircleColliderComponent");

		m_input.Initialize();
		m_renderer.Initialize("Game Engine", resolution_x, resolution_y);
		m_audio.Initialize();
		m_particle_system.Initialize(5000);
		m_physics.Initialize();

		Random::SetResolution(resolution_x, resolution_y);

		std::cout << "Engine initialized!" << "\n";
		return true;
	}

	void Engine::Shutdown() {
		m_input.Shutdown();
		m_renderer.Shutdown();
		m_particle_system.Shutdown();
		m_physics.Shutdown();
	}

	void Engine::Update() {
		m_input.Update();
		m_time.Tick();
		m_particle_system.Update(m_time.GetDeltaTime());
		if (m_scene_manager.GetActiveScene()) {
			m_scene_manager.GetActiveScene()->Update(m_time.GetDeltaTime());
			//m_scene_manager.GetActiveScene()->UpdateCollisions();
		}
		m_physics.Update(m_time.GetDeltaTime());
	}

	void Engine::UpdateAudio() {
		m_audio.Update();
	}
}
