#pragma once

#include <string>

#include "Actor.h"

namespace bnhe {
	class Scene {
	public:
		Scene(std::string name) : name{ name } {}
		std::string name = "Scene";

		void AddActor(Actor* actor) 
		{ 
			actor->m_scene = this;
			m_pending_actors.push_back(actor);
		}

		void RemoveActor(Actor* actor)
		{
			std::erase(m_actors, actor);
			delete actor;
			actor = nullptr;
		}

		void Clear() {
			for (auto actor : m_actors) {
				delete actor;
				actor = nullptr;
			}
			m_actors.clear();
		}

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

		void UpdateCollisions();

	private:
		std::vector<Actor*> m_actors;

		std::vector<Actor*> m_pending_actors;
		void AddPendingActors() {
			for (auto* actor : m_pending_actors) {
				m_actors.push_back(actor);
			}
			m_pending_actors.clear();
		}
	};
}