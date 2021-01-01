#pragma once

#include "Elements/Element.h"

class Xbox : public Element
{
public:
	Xbox(const std::string& label);

	virtual void OnRender() override;
};
