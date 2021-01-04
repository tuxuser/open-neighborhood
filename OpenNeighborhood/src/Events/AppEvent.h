#pragma once

#include "Events/Event.h"
#include "Elements/Element.h"

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizedEvent: " << m_Width << "," << m_Height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApp)
private:
	unsigned int m_Width, m_Height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() {}

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApp)
};

class ContentsChangeEvent : public Event
{
public:
	ContentsChangeEvent(Ref<std::vector<Ref<Element>>> elements, bool append = false)
		: m_Elements(elements), m_Append(append) {}

	inline Ref<std::vector<Ref<Element>>> GetElements() const { return m_Elements; }
	inline bool Append() const { return m_Append; }

	EVENT_CLASS_TYPE(ContentsChange)
	EVENT_CLASS_CATEGORY(EventCategoryApp)
private:
	Ref<std::vector<Ref<Element>>> m_Elements;
	bool m_Append;
};
