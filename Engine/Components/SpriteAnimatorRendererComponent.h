#pragma once
#include "SpriteRendererComponent.h"

#include "Resources/ResourceManager.h"

namespace bnhe
{
	class SpriteAnimatorRendererComponent : public SpriteRendererComponent
	{
	public:
		CLASS_PROTOTYPE(SpriteAnimatorRendererComponent);

		struct SpriteAnimation
		{
			std::string name;
			float fps{ 10.f };
			bool loop{ true };
			res_t<class TextureFrames> textureFrames;
		};


		void OnStart() override;
		void Update(float delta) override;

		void Play(const std::string& name);
		bool GetPause() const { return m_pause; }
		void SetPause(bool pause) { m_pause = pause; }

		unsigned int GetFrame() const { return m_frame; }
		const std::string GetCurrentAnimationName() const { return m_spriteAnimation.name; }

		void Read(const json::value_t& value) override;

	private:
		unsigned int m_frame = 0;
		float m_frameTimer = 0.f;
		bool m_pause{ false };

		std::string m_defaultAnimationName;
		SpriteAnimation m_spriteAnimation;
		std::map<std::string, SpriteAnimation> m_spriteAnimations;
	};
}