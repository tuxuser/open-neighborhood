#pragma once

#include <imgui.h>
#include <imgui_custom_widgets.h>

#include "Events/Event.h"

class Element
{
public:
	Element(const std::string& label, const std::string& textureName)
		: m_Label(label), m_TextureName(textureName) {}

	virtual ~Element() = default;

	virtual void OnRender() = 0;

	std::string GetLabel() const { return m_Label; }
	std::string GetTextureName() const { return m_TextureName; }

	using EventCallbackFn = std::function<void(Event&)>;
	void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }
protected:
	std::string m_Label;
	std::string m_TextureName;
	EventCallbackFn m_EventCallback;
};
