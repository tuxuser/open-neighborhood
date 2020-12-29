#include "pch.h"
#include "Elements/AddXboxButton.h"

#include "Render/TextureManager.h"

AddXboxButton::AddXboxButton() 
	: Element("Add Xbox 360", "addXboxButton") {}

void AddXboxButton::OnRender()
{
	ImGui::ImageButtonWithText((void*)(intptr_t)TextureManager::GetTexture(m_TextureName)->GetTextureID(), ImVec2(100.0f, 100.0f), m_Label.c_str());
}
