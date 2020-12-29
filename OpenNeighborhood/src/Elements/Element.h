#pragma once

#include <imgui.h>
#include <imgui_custom_widgets.h>

class Element
{
public:
	Element(const std::string& label, const std::string& textureName)
		: m_Label(label), m_TextureName(textureName) {}

	virtual ~Element() = default;

	virtual void OnRender() = 0;

	std::string GetLabel() const { return m_Label; }
	std::string GetTextureName() const { return m_TextureName; }
protected:
	std::string m_Label;
	std::string m_TextureName;
};
