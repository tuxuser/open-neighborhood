#include "pch.h"
#include "Panels/ContentsPanel.h"
#include "Render/TextureManager.h"

ContentsPanel::ContentsPanel()
{
	TextureManager::AddTexture("addXboxButton", "assets/icons/addXboxButton.png");
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
	ImGui::ImageButtonWithText((void*)(intptr_t)TextureManager::GetTexture("addXboxButton")->GetTexture(), ImVec2(100.0f, 100.0f), "Add Xbox 360");
	ImGui::End();
}
