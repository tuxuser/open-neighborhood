#pragma once

#include <imgui.h>

#include "Events/Event.h"

class Panel
{
public:
	virtual ~Panel() = default;

	virtual void OnRender() = 0;
	virtual void OnEvent(Event& event) {}
protected:
	float m_Margin = 20.0f;
};
