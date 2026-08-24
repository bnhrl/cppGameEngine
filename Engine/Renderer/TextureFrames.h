#pragma once
#include "Resource.h"

#include <string>

#include "Renderer.h"
#include "Math/Rect.h"

namespace bnhe 
{
	class TextureFrames : public Resource 
	{
	public:
		bool Load(const std::string& filename, class Renderer& renderer);
		Rect GetFrameRect(int frame);

	private:
		int m_numColumns    = 0;
		int m_numRows       = 0;
		int m_startFrame    = 0;
		int m_totalFrames   = 0;
		Vector2 m_frameSize{ 0 };
		res_t<class Texture> m_texture;
	};
}