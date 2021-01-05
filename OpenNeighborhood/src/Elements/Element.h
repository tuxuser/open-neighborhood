#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_custom_widgets.h>

#include "Events/Event.h"

class Element
{
public:
	Element(const std::string& label, const std::string& textureName, const std::string& errorMessage);

	virtual ~Element() = default;

	virtual void OnRender();
	virtual void OnClick() = 0;

	inline std::string GetLabel() const { return m_Label; }
	inline std::string GetTextureName() const { return m_TextureName; }
	inline float GetWidth() const { return m_Width; }
	inline float GetHeight() const { return m_Height; }

	using EventCallbackFn = std::function<void(Event&)>;
	inline void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }
protected:
	std::string m_Label;
	std::string m_TextureName;
	float m_Width;
	float m_Height;
	float m_Padding = 10.0f;
	EventCallbackFn m_EventCallback;

	// XBDM related members
	bool m_Success = true; // Gets set to false whenever an XBDM operation related to the element fails
	std::string m_ErrorMessage; // Gets printed in a modal window whenever an XBDM operation related to the element fails
};
