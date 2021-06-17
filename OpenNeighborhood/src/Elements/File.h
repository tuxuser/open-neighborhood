#pragma once

#include <XBDM.h>

#include "Elements/Element.h"

class File : public Element
{
public:
	File(const XBDM::File& data);

	virtual void OnClick() override;
private:
	XBDM::File m_Data;

	void OpenDirectory();
};
