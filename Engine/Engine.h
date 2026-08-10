#pragma once

#include "File.h"

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"
#include "MathUtils.h"
#include "Font.h"
#include "Text.h"
#include "Texture.h"

#include "GameTime.h"
#include "Renderer.h"
#include "Input.h"
#include "Audio.h"
#include "ParticleSystem.h"
#include "Scene.h"
#include "Actor.h"

#include "SceneManager.h"
#include "ResourceManager.h"


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
	};
}