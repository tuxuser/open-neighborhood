#include "pch.h"
#include "Panels/PathPanel.h"

#include "Core/App.h"

PathPanel::PathPanel()
{
	SetWindowWidthAndHeight();
}

void PathPanel::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(PathPanel::OnWindowResize));
}

void PathPanel::OnRender()
{
	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(m_Margin, m_Margin));
	ImGui::SetNextWindowSize(ImVec2((float)m_WindowWidth - m_Margin * 2.0f, m_Margin * 5.0f));

	ImGui::Begin("Path Window", nullptr, windowFlags);
	ImGui::End();
}

bool PathPanel::OnWindowResize(WindowResizeEvent& event)
{
	SetWindowWidthAndHeight();
	return true;
}

void PathPanel::SetWindowWidthAndHeight()
{
	App& app = App::Get();
	m_WindowWidth = app.GetWindow().GetWidth();
	m_WindowHeight = app.GetWindow().GetHeight();
}
