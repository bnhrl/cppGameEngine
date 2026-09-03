#include "pch.h"
#include "Components/SpriteRendererComponent.h"

#include "Engine.h"
#include "Core/Factory.h"

namespace bnhe {
	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::OnStart()
	{
		if (!m_textureName.empty()) 
		{
			m_texture = Resources().Get<Texture>(m_textureName, Engine::Get().GetRenderer());
			if (m_texture)
			{
				m_size = m_texture->GetSize();
			}
		}
	}

	void SpriteRendererComponent::Draw(const Renderer& renderer)
	{
		if (m_texture)
		{
			if (m_sourceRect.w > 0 && m_sourceRect.h > 0)
				renderer.DrawTexture(*m_texture, m_sourceRect, GetOwner()->GetTransform(), GetOwner()->GetModulate(), m_flipH);
			else
				renderer.DrawTexture(*m_texture, GetOwner()->GetTransform(), GetOwner()->GetModulate(), m_flipH);
		}
	}

	void SpriteRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		JSON_READ_NAME(value, "texture", m_textureName);
		JSON_READ_NAME(value, "flip_h", m_flipH);
	}
}