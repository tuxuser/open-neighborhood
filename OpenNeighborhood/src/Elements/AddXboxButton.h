#pragma once

#include "Elements/Element.h"

class AddXboxButton : public Element
{
public:
	AddXboxButton();

	virtual void OnRender() override;
private:
	void AddXbox(const std::string& ipAddress);
};
