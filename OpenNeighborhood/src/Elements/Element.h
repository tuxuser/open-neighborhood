#pragma once

#include <imgui.h>
#include <imgui_custom_widgets.h>

#include "Events/Event.h"

class Element
{
public:
	Element(const std::string& label, const std::string& textureName, float width = 0.0f, float height = 0.0f)
		: m_Label(label), m_TextureName(textureName), m_Width(width), m_Height(height) {}

	virtual ~Element() = default;

	virtual void OnRender() = 0;

	std::string GetLabel() const { return m_Label; }
	std::string GetTextureName() const { return m_TextureName; }
	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }

	using EventCallbackFn = std::function<void(Event&)>;
	void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }
protected:
	std::string m_Label;
	std::string m_TextureName;
	float m_Width;
	float m_Height;
	EventCallbackFn m_EventCallback;
};
