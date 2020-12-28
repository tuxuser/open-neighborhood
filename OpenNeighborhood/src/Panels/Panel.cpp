#include "pch.h"
#include "Panels/Panel.h"

#include "Core/App.h"

Panel::Panel()
{
	SetWindowWidthAndHeight();
}

void Panel::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Panel::OnWindowResize));
}

bool Panel::OnWindowResize(WindowResizeEvent& event)
{
	SetWindowWidthAndHeight();
	return true;
}

void Panel::SetWindowWidthAndHeight()
{
	App& app = App::Get();
	m_WindowWidth = app.GetWindow().GetWidth();
	m_WindowHeight = app.GetWindow().GetHeight();
}
