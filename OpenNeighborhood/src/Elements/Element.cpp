#include "pch.h"
#include "Elements/Element.h"

#include "Render/TextureManager.h"

Element::Element(const std::string& label, const std::string& textureName, const std::string& errorMessage)
	: m_Label(label), m_TextureName(textureName), m_ErrorMessage(errorMessage)
{
	if (!TextureManager::TextureExists(textureName))
		TextureManager::AddTexture(textureName, WORKING_DIR"assets/icons/" + textureName + ".png");

	auto texture = TextureManager::GetTexture(textureName);
	m_Width = texture->GetWidth() * 3;
	m_Height = texture->GetHeight();
}

void Element::OnRender()
{
	auto texture = TextureManager::GetTexture(m_TextureName);

	if (ImGui::ImageButtonWithText((void*)(intptr_t)texture->GetTextureID(), ImVec2((float)texture->GetWidth(), (float)texture->GetHeight()), ImVec2((float)m_Width, (float)m_Height), m_Label.c_str(), ImVec2(m_Padding, m_Padding)))
		OnClick();

	if (!m_Success)
	{
		ImGui::OpenPopup("Connection failed!");

		ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	}

	if (ImGui::BeginPopupModal("Connection failed!", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text(m_ErrorMessage.c_str());

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			m_Success = true;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}
