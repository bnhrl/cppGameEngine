#pragma once

#include <string>
#include <memory>

#include "Framework/Actor.h"

namespace bnhe {
	class Scene {
	public:
		Scene(std::string name) : name{ name } {}
		std::string name = "Scene";

		bool Load(const std::string& sceneName);

		void AddActor(std::unique_ptr<Actor> actor)
		{ 
			actor->m_scene = this;
			m_pending_actors.push_back(std::move(actor));
		}

		void RemoveActor(std::unique_ptr<Actor> actor)
		{
			std::erase(m_actors, actor);
		}

		void Clear() {
			m_actors.clear();
		}

		void Update(float delta);
		void Draw(const class Renderer& renderer);

		void UpdateCollisions();

	private:
		std::vector<std::unique_ptr<Actor>> m_actors;

		std::vector<std::unique_ptr<Actor>> m_pending_actors;
		void AddPendingActors() {
			for (auto& actor : m_pending_actors) {
				actor->OnStart();
				m_actors.push_back(std::move(actor));
			}
			m_pending_actors.clear();
		}
	};
}