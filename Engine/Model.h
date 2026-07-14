#pragma once

#include "Mesh.h"

#include <vector>

namespace bnhe {
	class Model {
	public:
		Model() = default;
		Model(const std::vector<Mesh>& meshes) : m_meshes{ meshes } {}

		void SetMeshes(const std::vector<Mesh>& meshes) { m_meshes = meshes; }
		const std::vector<Mesh>& GetMeshes() const { return m_meshes; }

	private:
		std::vector<Mesh> m_meshes;
	};
}