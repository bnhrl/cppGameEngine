#include "pch.h"
#include "Scene.h"

namespace bnhe {
	void Scene::Update(float delta) {
		for (const auto& actor : m_actors) {
			if (!actor || actor.get()->IsDestroyed()) continue;
			actor.get()->Update(delta);
		}

		// Remove destroyed actors
		std::erase_if(m_actors, [](auto& actor) { return actor->IsDestroyed(); });

		AddPendingActors();
	}

	void Scene::Draw(const class Renderer& renderer) {
		for (const auto& actor : m_actors) {
			if (actor)  actor->Draw(renderer);
		}
	}

	void Scene::UpdateCollisions() {
		for (const auto& actorA : m_actors) {
			for (const auto& actorB : m_actors) {
				if (actorA == actorB || actorA->destroyed || actorB->destroyed) break;

				float distance = (actorA->GetTransform().position.DistanceTo(actorB->GetTransform().position));
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
}