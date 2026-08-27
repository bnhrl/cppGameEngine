#pragma once
#include "Framework/Object.h"

namespace bnhe {
	class Actor;

	class Component : public Object {
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void Read(const json::value_t& value) {};

		virtual void OnStart() {}
		virtual void OnDestroy() {}

		virtual void Update(float delta) {}

		Actor* GetOwner() const { return m_owner; }
		void SetOwner(Actor* owner) { m_owner = owner; }

	protected:
		Actor* m_owner = nullptr;
	};
}