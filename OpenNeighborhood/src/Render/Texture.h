#pragma once

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(uint32_t slot = 0) const;

	inline uint32_t GetTextureID() const { return m_RendererID; }
	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }
private:
	uint32_t m_RendererID;
	uint32_t m_Width, m_Height;
};
