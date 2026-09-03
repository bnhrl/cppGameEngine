#pragma once
#include "Components/RendererComponent.h"

#include "Core/Factory.h"

namespace bnhe {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)

		virtual void OnStart() override;
		virtual void Draw(const Renderer& renderer) override;

		const Vector2& GetSize() const { return m_size; }
		
		bool GetFlipH() const { return m_flipH; }
		void SetFlipH(bool flip = true) { m_flipH = flip; }

		virtual void Read(const json::value_t& value) override;

	protected:
		std::string m_textureName;
		Rect m_sourceRect;
		Vector2 m_size{ 0.f, 0.f };
		bool m_flipH = false;

		res_t<Texture> m_texture;
	};
}