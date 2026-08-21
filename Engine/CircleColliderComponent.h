#pragma once
#include "ColliderComponent.h"

namespace bnhe {
	class CircleColliderComponent : public ColliderComponent {
	public:
		CLASS_PROTOTYPE(CircleColliderComponent)

		virtual bool CheckCollision(const ColliderComponent& other) override;

		void Read(const json::value_t& value) override;

		float GetRadius() const { return m_radius; }
	protected:
		bool m_radius;
	};
}