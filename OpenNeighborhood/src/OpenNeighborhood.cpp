#include "pch.h"
#include "OpenNeighborhood.h"

#include "Render/UI.h"
#include "Panels/MainPanel.h"
#include "Panels/PathPanel.h"
#include "Panels/ContentsPanel.h"

OpenNeighborhood::OpenNeighborhood()
	: Layer("OpenNeighborhood") {}

void OpenNeighborhood::OnAttach()
{
	UI::Init();

	m_PanelStack.Push(new MainPanel());
	m_PanelStack.Push(new PathPanel());
	m_PanelStack.Push(new ContentsPanel());
}

void OpenNeighborhood::OnDetach()
{
	UI::Cleanup();
}

void OpenNeighborhood::OnEvent(Event& event)
{

}

void OpenNeighborhood::OnUpdate(Timestep ts)
{
	UI::BeginFrame();

	for (Panel* panel : m_PanelStack)
		panel->OnRender();

	UI::EndFrame();
}
