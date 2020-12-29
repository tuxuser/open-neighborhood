#pragma once

#include "Panels/Panel.h"
#include "Elements/Element.h"

class ContentsPanel : public Panel
{
public:
	ContentsPanel();

	virtual void OnRender() override;
private:
	std::vector<Ref<Element>> m_Elements;
};
