#include "pch.h"
#include "OpenNeighborhood.h"

#include "Render/UI.h"
#include "Panels/MainPanel.h"
#include "Panels/PathPanel.h"
#include "Panels/ContentsPanel.h"

#include "Events/AppEvent.h"

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
	for (Panel* panel : m_PanelStack)
		panel->OnEvent(event);
}

void OpenNeighborhood::OnUpdate(Timestep ts)
{
	UI::BeginFrame();

	for (auto it = m_PanelStack.end(); it != m_PanelStack.begin();)
		(*--it)->OnRender();

	UI::EndFrame();
}
