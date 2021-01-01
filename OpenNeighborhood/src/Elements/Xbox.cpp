#include "pch.h"
#include "Elements/Xbox.h"

#include "Render/TextureManager.h"

Xbox::Xbox(const std::string& label)
	: Element(label, "xbox", 100.0f, 100.0f) {}

void Xbox::OnRender()
{
	ImGui::ImageButtonWithText((void*)(intptr_t)TextureManager::GetTexture(m_TextureName)->GetTextureID(), ImVec2(m_Width, m_Height), m_Label.c_str());
}
