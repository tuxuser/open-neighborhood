#include "pch.h"
#include "Elements/Element.h"

#include "Render/TextureManager.h"

Element::Element(const std::string& label, const std::string& textureName, float width, float height)
	: m_Label(label), m_TextureName(textureName), m_Width(width), m_Height(height)
{
	if (TextureManager::TextureExists(textureName))
		return;

	TextureManager::AddTexture(textureName, WORKING_DIR"assets/icons/" + textureName + ".png");
}
