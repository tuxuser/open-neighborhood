#include "pch.h"
#include "Elements/Drive.h"

#include "Render/TextureManager.h"

Drive::Drive(const XBDM::Drive& data)
	: m_Data(data), Element(data.FriendlyName, "drive", "Couldn't fetch content from this drive!") {}

void Drive::OnClick()
{
	
}
