#include "pch.h"
#include "Panels/PathPanel.h"

void PathPanel::OnRender()
{
	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(m_Margin, m_Margin));
	ImGui::SetNextWindowSize(ImVec2((float)m_WindowWidth - m_Margin * 2.0f, m_Margin * 5.0f));

	ImGui::Begin("Path Window", nullptr, windowFlags);
	ImGui::End();
}
