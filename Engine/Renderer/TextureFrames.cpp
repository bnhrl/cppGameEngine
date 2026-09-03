#include "pch.h"
#include "TextureFrames.h"

#include "Serialization/Json.h"
#include "Resources/ResourceManager.h"

namespace bnhe
{
	bool TextureFrames::Load(const std::string& filename, class Renderer& renderer) {
		json::document_t document;

		if (!json::Load(filename, document)) 
		{
			std::cerr << "Could not load JSON document for TextureFrames: " << filename << std::endl;
			return false;
		}

		std::string texture_name;
		JSON_READ_REQ(document, texture_name);

		if (texture_name.empty()) {
			std::cerr << "Could not get texture name for TextureFrames: " << filename << std::endl;
			return false;
		}

		m_texture = Resources().Get<Texture>(texture_name, renderer);

		if (!m_texture) {
			std::cerr << "Could not load Texture for TextureFrames: " << filename << std::endl;
			return false;
		}
		
		JSON_READ_NAME(document, "columns", m_numColumns);
		JSON_READ_NAME(document, "rows", m_numRows);
		JSON_READ_NAME(document, "start_frame", m_startFrame);
		JSON_READ_NAME(document, "total_frames", m_totalFrames);

		if (m_numColumns <= 0) m_numColumns = 1;
		if (m_numRows <= 0) m_numRows = 1;

		Vector2 textureSize = m_texture->GetSize();
		m_frameSize = textureSize / Vector2(m_numColumns, m_numRows);

		return true;
	}

	Rect TextureFrames::GetFrameRect(int frame)
	{
		if (frame >= m_totalFrames)
		{
			std::cerr << "Frame " << frame << " of TextureFrames is out of bounds.\n";
        
		}
		int currentFrame = m_startFrame + frame;
		int column = currentFrame % m_numColumns;
		int row = currentFrame / m_numColumns;

		float x = column * m_frameSize.x;
		float y = row * m_frameSize.y;

		return Rect{ x, y, m_frameSize.x, m_frameSize.y };
	}
}