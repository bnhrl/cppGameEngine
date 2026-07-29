#pragma once

#include <vector>

#include "Color.h"
#include "Vector2.h"

namespace bnhe {
	struct Particle
	{
		bool active{ false };
		float lifespan{ 1 };

		Vector2 position{ 0, 0 };
		Vector2 velocity{ 0, 0 };
		Color targetColor{ 1, 1, 1, 1 };
		Color color{ 1, 1, 1, 1 };
	};

	class ParticleSystem {
	public:
		bool Initialize(size_t size);

		void Update(float delta);
		void Draw(const class Renderer& renderer);

		void AddParticle(const Particle& particle);

		void Shutdown();

	private:
		std::vector<Particle> m_particles;
		Particle* GetFreeParticle();
	};
}