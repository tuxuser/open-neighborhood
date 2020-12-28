#include "pch.h"
#include "Panels/ContentsPanel.h"

#include "Core/App.h"

ContentsPanel::ContentsPanel()
{
	SetWindowWidthAndHeight();
}

void ContentsPanel::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ContentsPanel::OnWindowResize));
}

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

bool ContentsPanel::OnWindowResize(WindowResizeEvent& event)
{
	SetWindowWidthAndHeight();
	return true;
}

void ContentsPanel::SetWindowWidthAndHeight()
{
	App& app = App::Get();
	m_WindowWidth = app.GetWindow().GetWidth();
	m_WindowHeight = app.GetWindow().GetHeight();
}
