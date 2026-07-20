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
}