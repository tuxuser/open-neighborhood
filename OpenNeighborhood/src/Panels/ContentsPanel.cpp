#include "pch.h"
#include "Panels/ContentsPanel.h"

ContentsPanel::ContentsPanel()
{
	m_Textures["addXboxButton"] = std::make_shared<Texture>("assets/icons/addXboxButton.png");
	m_Textures["ChernoLogo"] = std::make_shared<Texture>("assets/icons/ChernoLogo.png");

	for (auto& texture : m_Textures)
	{
		texture.second->Bind(m_TextureCount);
		m_TextureCount++;
	}
}

void ContentsPanel::OnRender()
{
	float pathPanelSize = m_Margin * 5.0f;

	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(m_Margin, m_Margin * 2.0f + pathPanelSize));
	ImGui::SetNextWindowSize(ImVec2((float)m_WindowWidth - m_Margin * 2.0f, (float)m_WindowHeight - (m_Margin * 3.0f + pathPanelSize)));

	ImGui::Begin("Contents Window", nullptr, windowFlags);
	ImGui::ImageButtonWithText((void*)(intptr_t)m_Textures.find("addXboxButton")->second->GetTexture(), ImVec2(100.0f, 100.0f), "Add Xbox 360");
	ImGui::End();
}
