#pragma once
#include "Component.h"
#include "Renderer.h"

namespace bnhe {
	class RendererComponent : public Component {
	public:
		CLASS_PROTOTYPE(RendererComponent)

		virtual void Draw(const Renderer& renderer) {}

		virtual void Read(const json::value_t& value) override {};
	};
}