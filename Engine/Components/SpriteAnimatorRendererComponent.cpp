#include "pch.h"
#include "SpriteAnimatorRendererComponent.h"

#include "Renderer/TextureFrames.h"
#include "Core/Factory.h"
#include "Core/StringUtils.h"
#include "Engine.h"

namespace bnhe
{
	FACTORY_REGISTER(SpriteAnimatorRendererComponent)

	void SpriteAnimatorRendererComponent::OnStart()
	{
		// Play default animation or default to first element in map
		if (!m_defaultAnimationName.empty()) Play(m_defaultAnimationName);
		else 
		{
			auto iter = m_spriteAnimations.begin();
			std::string name = iter->first;
			Play(name);
		}
	}

	void SpriteAnimatorRendererComponent::Update(float delta)
	{
		if (!m_spriteAnimation.textureFrames) return;

		m_frameTimer += delta;
		float frameTime = 1.0f / m_spriteAnimation.fps;

		// increase frame while frame timer is greater than frame time
		while (m_frameTimer >= frameTime)
		{
			m_frame++;

			if (m_spriteAnimation.loop)
			{
				// Loop back down to zero
				if (m_frame >= m_spriteAnimation.textureFrames->GetTotalFrames()) m_frame = 0;
			}
			else
			{
				if (m_frame >= m_spriteAnimation.textureFrames->GetTotalFrames() - 1) {
					m_frame = m_spriteAnimation.textureFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
			m_sourceRect = m_spriteAnimation.textureFrames->GetFrameRect(m_frame);
		}
	}


	void SpriteAnimatorRendererComponent::Play(const std::string& name)
	{
		if (string::EqualsIgnoreCase(name, m_spriteAnimation.name)) return;

		auto iter = m_spriteAnimations.find(name);
		if (iter == m_spriteAnimations.end())
		{
			return;
		}

		m_spriteAnimation = iter->second;

		m_frame = 0;
		m_frameTimer = 0.f;

		m_texture = m_spriteAnimation.textureFrames->GetTexture();
	}

	void SpriteAnimatorRendererComponent::Read(const json::value_t& value)
	{
		SpriteRendererComponent::Read(value);

		JSON_READ_NAME(value, "default_animation", m_defaultAnimationName);

		if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray())
		{
			for (auto& animatorValue : JSON_GET(value, animations).GetArray())
			{
				SpriteAnimation spriteAnimation;

				std::string textureAnimationName;

				JSON_READ_NAME(animatorValue, "name", spriteAnimation.name);

				std::string texture_frames;
				JSON_READ_REQ(animatorValue, texture_frames);

				if (!texture_frames.empty())
				{
					spriteAnimation.textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
					if (!spriteAnimation.textureFrames)
					{
						std::cerr << "Could not load texture frames: " << texture_frames << std::endl;
					}
				}

				JSON_READ_NAME_REQ(animatorValue, "fps", spriteAnimation.fps);
				JSON_READ_NAME(animatorValue, "loop", spriteAnimation.loop);

				m_spriteAnimations[string::ToLower(spriteAnimation.name)] = spriteAnimation;
			}
		}

	}
}