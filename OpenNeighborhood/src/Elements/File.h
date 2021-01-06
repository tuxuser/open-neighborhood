#pragma once

#include <XBDM.h>

#include "Elements/Element.h"

class File : public Element
{
public:
	File(const XBDM::FileEntry& data);

	virtual void OnClick() override;
private:
	XBDM::FileEntry m_Data;
};
