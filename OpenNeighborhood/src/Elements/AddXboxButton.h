#pragma once

#include "Elements/Element.h"

class AddXboxButton : public Element
{
public:
	AddXboxButton();

	virtual void OnRender() override;
private:
	void CreateXbox(const std::string& consoleName, const std::string& ipAddress);
};
