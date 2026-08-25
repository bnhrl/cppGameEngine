#pragma once

#include "Renderer/Mesh.h"

#include <vector>

namespace bnhe {
	class Model {
	public:
		Model() = default;
		Model(const std::vector<Mesh>& meshes) : m_meshes{ meshes } { CalculateRadius(); }

		void AddMesh(const Mesh& mesh) { m_meshes.push_back(mesh); CalculateRadius(); }
		void SetMeshes(const std::vector<Mesh>& meshes) { m_meshes = meshes; CalculateRadius(); }
		void SetMeshColor(const Color& color) { 
			for (Mesh &mesh : m_meshes) {
				mesh.SetColor(color);
			}
		}
		const std::vector<Mesh>& GetMeshes() const { return m_meshes; }

		float GetRadius() const { return m_radius; }
		float CalculateRadius();

	private:
		float m_radius = 0.0f;
		std::vector<Mesh> m_meshes;
	};
}