#include "pch.h"
#include "Panels/MainPanel.h"

void MainPanel::OnRender()
{
	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2((float)m_WindowWidth, (float)m_WindowHeight));

	ImGui::Begin("Main Window", nullptr, windowFlags);
	ImGui::End();
}
