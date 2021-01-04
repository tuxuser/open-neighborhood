#include "pch.h"
#include "Elements/Drive.h"

#include "Render/TextureManager.h"

Drive::Drive(const XBDM::Drive& data)
	: m_Data(data), Element(data.FriendlyName, "drive", 100.0f, 100.0f) {}

void Drive::OnRender()
{
	ImGui::ImageButtonWithText((void*)(intptr_t)TextureManager::GetTexture(m_TextureName)->GetTextureID(), ImVec2(m_Width, m_Height), m_Label.c_str());
}
