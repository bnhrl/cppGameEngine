#include "pch.h"
#include "SpriteAnimationRendererComponent.h"

#include "Core/Factory.h"
#include "Resources/ResourceManager.h"
#include "Engine.h"

namespace bnhe 
{
	FACTORY_REGISTER(SpriteAnimationRendererComponent)

	void SpriteAnimationRendererComponent::OnStart()
	{
		if (!m_textureFramesName.empty()) {
			m_textureFrames = Resources().Get<TextureFrames>(m_textureFramesName, Engine::Get().GetRenderer());
			if (m_textureFrames)
			{
				m_sourceRect = m_textureFrames->GetFrameRect(0);
				m_size = Vector2(m_sourceRect.x, m_sourceRect.y);
				m_texture = m_textureFrames->GetTexture();
			}
			else 
				std::cerr << "Could not load texture frames" << std::endl;

		}
		else {
			std::cerr << "Could not load texture frames" << std::endl;
		}
	}

	void SpriteAnimationRendererComponent::Update(float delta)
	{
		if (!m_textureFrames) return;

		m_frameTimer += delta;
		float frameTime = 1.0f / m_fps;

		// increase frame while frame timer is greater than frame time
		while (m_frameTimer >= frameTime) 
		{
			m_frame++;

			if (m_loop) 
			{
				// Loop back down to zero
				if (m_frame >= m_textureFrames->GetTotalFrames()) m_frame = 0;
			}
			else 
			{
				if (m_frame >= m_textureFrames->GetTotalFrames()-1) {
					m_frame = m_textureFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
			m_sourceRect = m_textureFrames->GetFrameRect(m_frame);
		}
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "fps", m_fps);
		JSON_READ_NAME(value, "loop", m_loop);

		JSON_READ_NAME_REQ(value, "texture_frames", m_textureFramesName);
	}
}