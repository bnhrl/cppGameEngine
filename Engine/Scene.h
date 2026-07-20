#pragma once

#include "Actor.h"

namespace bnhe {
	class Scene {
	public:
		void AddActor(Actor* actor) { m_actors.push_back(actor); }

		void Update(float delta);
		void Draw(const class Renderer& renderer);

	private:
		std::vector<Actor*> m_actors;
	};
}