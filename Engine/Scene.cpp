#include "pch.h"
#include "Scene.h"

#include "ColliderComponent.h"
#include "Factory.h"

namespace bnhe {
	bool Scene::Load(const std::string& sceneName)
	{
		json::document_t document;
		if (json::Load(sceneName, document))
		{
			if (JSON_HAS_NAME(document, "actors"))
			{
				for (auto& actorValue : JSON_GET_NAME(document, "actors").GetArray())
				{
					std::string typeName;
					JSON_READ_NAME(actorValue, "type", typeName);

					auto actor = Factory::Instance().Create<Actor>(typeName);
					actor->Read(actorValue);

					bool prototype = false;
					JSON_READ(actorValue, prototype);

					if (prototype)
					{
						std::string name;
						JSON_READ(actorValue, name);
						Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
					}
					else
					{
						AddActor(std::move(actor));
					}
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}

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
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || actorA->destroyed || actorB->destroyed) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorA->GetComponent<ColliderComponent>();
				
				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) 
				{
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
}