#pragma once

#include "Render/Texture.h"

class TextureManager
{
public:
	static void AddTexture(const std::string& textureName, const std::string& filePath);
	static Ref<Texture> GetTexture(const std::string& textureName);
private:
	static std::unordered_map<std::string, Ref<Texture>> s_Textures;
	static uint32_t s_TextureCount;
};
