#pragma once

#include "File.h"

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"
#include "MathUtils.h"

#include "GameTime.h"
#include "Renderer.h"
#include "Input.h"
#include "Scene.h"
#include "Actor.h"


namespace bnhe 
{
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize(int resolution_x = 1280, int resolution_y = 720);
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }

	private:
		Engine() = default;

		Input m_input;
		Renderer m_renderer;
		Time m_time;
	};
}