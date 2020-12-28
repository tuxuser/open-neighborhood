#include "pch.h"
#include "Panels/ContentsPanel.h"

#include "Core/App.h"

void ContentsPanel::OnRender()
{
	App& app = App::Get();
	unsigned int windowWidth = app.GetWindow().GetWidth();
	unsigned int windowHeight = app.GetWindow().GetHeight();

	float pathPanelSize = m_Margin * 5.0f;

	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(m_Margin, m_Margin * 2.0f + pathPanelSize));
	ImGui::SetNextWindowSize(ImVec2((float)windowWidth - m_Margin * 2.0f, (float)windowHeight - (m_Margin * 3.0f + pathPanelSize)));

	ImGui::Begin("Contents Window", nullptr, windowFlags);
	ImGui::End();
}
