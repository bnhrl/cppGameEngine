#pragma once
#include "RendererComponent.h"

#include "Resources/Resource.h"
#include "Renderer/TextureFrames.h"

namespace bnhe {
	class SpriteAnimationRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent)

		void Update(float delta) override;
		void Draw(const Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	private:
		float m_fps = 1.0f;
		bool m_loop = true;

		unsigned int m_frame;
		float m_frameTimer = 0.f;

		res_t<TextureFrames> m_textureFrames;
	};
}