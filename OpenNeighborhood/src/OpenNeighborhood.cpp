#include "pch.h"
#include "OpenNeighborhood.h"

#include "Render/UI.h"

OpenNeighborhood::OpenNeighborhood()
	: Layer("OpenNeighborhood") {}

void OpenNeighborhood::OnAttach()
{
	UI::Init();
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

	m_MainPanel.OnRender();
	m_PathPanel.OnRender();

	UI::EndFrame();
}
