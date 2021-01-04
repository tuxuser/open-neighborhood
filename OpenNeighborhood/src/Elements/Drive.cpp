#include "pch.h"
#include "Elements/Drive.h"

#include "Render/TextureManager.h"

Drive::Drive(const XBDM::Drive& data)
	: m_Data(data), Element(data.FriendlyName, "drive", 100.0f, 100.0f, "Couldn't fetch content from this drive!") {}

void Drive::OnClick()
{
	
}
