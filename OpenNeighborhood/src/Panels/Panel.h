#pragma once

#include <imgui.h>
#include <imgui_custom_widgets.h>

#include "Events/AppEvent.h"

class Panel
{
public:
	Panel();
	virtual ~Panel() = default;

	virtual void OnRender() = 0;
	virtual void OnEvent(Event& event);
protected:
	float m_Margin = 20.0f;
	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
private:
	bool OnWindowResize(WindowResizeEvent& event);
	void SetWindowWidthAndHeight();
};
