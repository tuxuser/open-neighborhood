#pragma once

#include <imgui.h>

class Panel
{
public:
	virtual ~Panel() = default;

	virtual void OnRender() = 0;
protected:
	float m_Margin = 20.0f;
};
