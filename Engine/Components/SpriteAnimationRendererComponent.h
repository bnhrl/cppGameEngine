#pragma once
#include "SpriteRendererComponent.h"

#include "Resources/Resource.h"
#include "Renderer/TextureFrames.h"

namespace bnhe {
	class SpriteAnimationRendererComponent : public SpriteRendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent)

		void OnStart() override;
		void Update(float delta) override;

		void Read(const json::value_t& value) override;
	private:
		float m_fps = 1.0f;
		bool m_loop = true;

		unsigned int m_frame = 0;
		float m_frameTimer = 0.f;

		std::string m_textureFramesName;

		res_t<TextureFrames> m_textureFrames;
	};
}