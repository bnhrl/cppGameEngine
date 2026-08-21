#pragma once
#include "RendererComponent.h"

#include "Factory.h"

namespace bnhe {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)

		virtual void Draw(const Renderer& renderer) override;

		virtual void Read(const json::value_t& value) override;

	protected:
		res_t<Texture> m_texture;
	};
}