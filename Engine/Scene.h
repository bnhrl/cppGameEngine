#pragma once

#include <string>

#include "Actor.h"

namespace bnhe {
	class Scene {
	public:
		void AddActor(Actor* actor) { actor->m_scene = this; m_actors.push_back(actor); }

		void Update(float delta);
		void Draw(const class Renderer& renderer);

		template<typename T>
		inline T* GetActorByName(const std::string& name) {
			for (auto actor : m_actors) {
				T* actorT = dynamic_cast<T*>(actor);
				if (actorT && actorT->m_name == name) {
					return actorT;
				}
			}
			
			return nullptr;
		}

	private:
		std::vector<Actor*> m_actors;
	};
}