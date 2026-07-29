#include "pch.h"
#include "ParticleSystem.h"

#include "Renderer.h";

namespace bnhe {
	bool ParticleSystem::Initialize(size_t size)
	{
		// reserve # particles in container
		m_particles.resize(size);

		return true;
	}

	void ParticleSystem::Update(float delta)
	{
		// update active particles
		for (auto& particle : m_particles)
		{
			if (!particle.active) continue;

			particle.lifespan -= delta;

			particle.active = particle.lifespan > 0;

			particle.position += particle.velocity * delta;

			particle.color = particle.targetColor * particle.lifespan;
		}
	}

	void ParticleSystem::Draw(const Renderer& renderer)
	{
		// draw all active particlee
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				renderer.SetColor(particle.color);
				renderer.DrawPoint(particle.position);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle)
	{
		// get free particle
		Particle* freeParticle = GetFreeParticle();
		// check if free particle is not nullptr
		if (freeParticle)
		{
			// set free particle object with particle
			freeParticle->color = particle.color;
			freeParticle->targetColor = particle.targetColor;
			freeParticle->lifespan = particle.lifespan;
			freeParticle->position = particle.position;
			freeParticle->velocity = particle.velocity;

			// set particle active
			freeParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		// find and return inactive particle 
		for (auto& particle : m_particles)
		{
			// return pointer to inactive particle
			if (!particle.active)
				return &particle;
		}

		// no free particles, return nullptr
		return nullptr;
	}

	void ParticleSystem::Shutdown()
	{
		// clear all particles
		// TODO: clear() particles
	}
}