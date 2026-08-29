#pragma once
#include "RendererComponent.h"

#include "Resources/ResourceManager.h"

namespace bnhe
{
	class TilemapRendererComponent : public RendererComponent
	{
	public:
		TilemapRendererComponent() = default;
		TilemapRendererComponent(const TilemapRendererComponent& other);

		CLASS_PROTOTYPE(TilemapRendererComponent);

		virtual void OnStart() override;
		virtual void Draw(const Renderer& renderer) override;

		virtual void Read(const json::value_t& value) override;

	private:
		std::string m_tilemapName;
		res_t<class Tilemap> m_tilemap;

		std::vector<std::unique_ptr<class PhysicsBody>> m_physicsBodies;
	};
}