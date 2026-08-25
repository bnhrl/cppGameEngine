#include "pch.h"
#include "SpriteAnimationRendererComponent.h"

#include "Core/Factory.h"
#include "Resources/ResourceManager.h"
#include "Engine.h"

namespace bnhe 
{
	FACTORY_REGISTER(SpriteAnimationRendererComponent)

	void SpriteAnimationRendererComponent::Update(float delta)
	{
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
		}
	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& renderer)
	{
		if (!m_textureFrames) return;

		auto transform = GetOwner()->GetTransform();
		renderer.DrawTexture(
			*m_textureFrames->GetTexture(), 
			m_textureFrames->GetFrameRect(m_frame), 
			transform, 
			GetOwner()->GetModulate());
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "fps", m_fps);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string texture_frames;
		JSON_READ_REQ(value, texture_frames);

		if (!texture_frames.empty()) {
			m_textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
		}
		else {
			std::cerr << "Could not load texture frames" << std::endl;
		}
	}

}