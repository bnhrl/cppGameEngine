#include "pch.h"
#include "Components/SpriteRendererComponent.h"

#include "Engine.h"
#include "Core/Factory.h"

namespace bnhe {
	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer)
	{
		renderer.DrawTexture(*m_texture, GetOwner()->GetTransform(), GetOwner()->GetModulate());
	}
	void SpriteRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		std::string textureName;
		JSON_READ_NAME(value, "texture", textureName);
		if (!textureName.empty()) {
			m_texture = Resources().Get<Texture>(textureName, Engine::Get().GetRenderer());
		}
	}
}