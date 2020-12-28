#pragma once

#include "Panels/Panel.h"
#include "Events/AppEvent.h"

class ContentsPanel : public Panel
{
public:
	ContentsPanel();

	virtual void OnRender() override;
	virtual void OnEvent(Event& event) override;
private:
	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;

	bool OnWindowResize(WindowResizeEvent& event);
	void SetWindowWidthAndHeight();
};
