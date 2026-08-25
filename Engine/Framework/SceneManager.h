#pragma once

#include "Framework/Scene.h"

namespace bnhe {
	class SceneManager {
	public:
		Scene* GetActiveScene() { return m_active_scene; }
		void SetActiveScene(std::string name) { m_active_scene = GetScene(name); }
		void AddScene(Scene* scene) { m_scenes.push_back(scene); if (m_active_scene == nullptr) SetActiveScene(scene->name); }
		Scene* GetScene(std::string name) { for (auto scene : m_scenes) { if (scene->name == name) return scene; } return nullptr; }

	private:
		Scene* m_active_scene = nullptr;
		std::vector<Scene*> m_scenes;
	};
}