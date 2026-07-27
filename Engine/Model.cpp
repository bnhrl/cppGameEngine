#include "pch.h"
#include "Model.h"

namespace bnhe 
{
	float Model::CalculateRadius() {
		m_radius = 0.0f;

		for (const Mesh& mesh : m_meshes) {
			float radius = mesh.GetRadius();

			if (radius < m_radius) m_radius = radius;
		}

		return m_radius;
	}
}