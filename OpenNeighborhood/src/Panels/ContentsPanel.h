#pragma once

#include "Panels/Panel.h"
#include "Elements/Element.h"

class ContentsPanel : public Panel
{
public:
	ContentsPanel();

	virtual void OnRender() override;
	virtual void OnEvent(Event& event);
private:
	std::vector<Ref<Element>> m_Elements;
	std::queue<ContentsChangeEvent> m_ContentsChangeEventQueue;

	bool OnContentsChange(ContentsChangeEvent& event);
	void UpdateEventCallbacks();
	void InjectNewElements();
};
