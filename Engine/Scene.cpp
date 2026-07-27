#include "pch.h"
#include "Scene.h"

namespace bnhe {
	void Scene::Update(float delta) {
		for (auto actor : m_actors) {
			actor->Update(delta);
		}
	}

	void Scene::Draw(const class Renderer& renderer) {
		for (auto actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	void Scene::UpdateCollisions() {
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB) break;

				float distance = (actorA->GetTransform().position.DistanceTo(actorB->GetTransform().position));
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB);
					actorB->OnCollision(actorA);
				}
			}
		}
	}
}