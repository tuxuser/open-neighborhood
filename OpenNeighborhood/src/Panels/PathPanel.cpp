#include "pch.h"
#include "Panels/PathPanel.h"

#include "Core/App.h"

void PathPanel::OnRender()
{
	App& app = App::Get();
	unsigned int windowWidth = app.GetWindow().GetWidth();
	unsigned int windowHeight = app.GetWindow().GetHeight();

	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(m_Margin, m_Margin));
	ImGui::SetNextWindowSize(ImVec2((float)windowWidth - m_Margin * 2.0f, m_Margin * 5.0f));

	ImGui::Begin("Path Window", nullptr, windowFlags);
	ImGui::End();
}
