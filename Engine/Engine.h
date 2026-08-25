#pragma once

#include "Framework/Object.h"
#include "Core/Factory.h"
#include "Core/File.h"

#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Math/MathUtils.h"
#include "Serialization/Json.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"

#include "Physics/Physics.h"
#include "Core/GameTime.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Audio/Audio.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"

#include "Framework/SceneManager.h"
#include "Resources/ResourceManager.h"


namespace bnhe 
{
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize(int resolution_x = 1280, int resolution_y = 720);
		void Shutdown();

		void Update();
		void UpdateAudio();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		Audio& GetAudio() { return m_audio; }
		ParticleSystem& GetPS() { return m_particle_system; }
		SceneManager& GetSM() { return m_scene_manager; }
		Physics& GetPhysics() { return m_physics; }
		res_t<Font> GetFont()    const { return Resources().GetWithID<Font>("Font", "Fonts/Pixelzone.ttf", 64); }
		res_t<Font> GetFontBig() const { return Resources().GetWithID<Font>("FontLarge", "Fonts/Pixelzone.ttf", 128); }

	private:
		Engine() = default;

		Input m_input;
		Renderer m_renderer;
		Time m_time;
		Audio m_audio;
		ParticleSystem m_particle_system;
		SceneManager m_scene_manager;
		Physics m_physics;
	};
}