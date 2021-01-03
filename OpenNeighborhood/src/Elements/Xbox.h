#pragma once

#include "Elements/Element.h"

class Xbox : public Element
{
public:
	Xbox(const std::string& label, const std::string& ipAddress);

	virtual void OnRender() override;
private:
	std::string m_IpAddress;
};
