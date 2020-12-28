#include "pch.h"
#include "Panels/ContentsPanel.h"

void ContentsPanel::OnRender()
{
	float pathPanelSize = m_Margin * 5.0f;

	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(m_Margin, m_Margin * 2.0f + pathPanelSize));
	ImGui::SetNextWindowSize(ImVec2((float)m_WindowWidth - m_Margin * 2.0f, (float)m_WindowHeight - (m_Margin * 3.0f + pathPanelSize)));

	ImGui::Begin("Contents Window", nullptr, windowFlags);
	ImGui::End();
}
