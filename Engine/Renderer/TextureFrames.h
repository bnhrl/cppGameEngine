#pragma once
#include "Resources/Resource.h"

#include <string>

#include "Renderer/Renderer.h"
#include "Math/Rect.h"

namespace bnhe 
{
	class TextureFrames : public Resource 
	{
	public:
		bool Load(const std::string& filename, class Renderer& renderer);
		Rect GetFrameRect(int frame);

		unsigned int GetTotalFrames() const { return m_totalFrames; }
		res_t<class Texture> GetTexture()   { return m_texture; }

	private:
		unsigned int m_numColumns    = 0;
		unsigned int m_numRows       = 0;
		unsigned int m_startFrame    = 0;
		unsigned int m_totalFrames   = 0;
		Vector2 m_frameSize{ 0 };
		res_t<class Texture> m_texture;
	};
}