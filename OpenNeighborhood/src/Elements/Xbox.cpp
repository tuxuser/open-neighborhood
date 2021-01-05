#include "pch.h"
#include "Elements/Xbox.h"

#include "Render/TextureManager.h"
#include "Xbox/XboxManager.h"
#include "Events/AppEvent.h"
#include "Elements/Drive.h"

Xbox::Xbox(const std::string& label, const std::string& ipAddress)
	: m_IpAddress(ipAddress), Element(label, "xbox", 240.0f, 80.0f, "Couldn't find console!") {}

void Xbox::OnClick()
{
	std::string consoleName;
	m_Success = XboxManager::CreateConsole(m_IpAddress, consoleName, true);

	if (m_Success)
	{
		Ref<std::vector<Ref<Element>>> driveElements = CreateRef<std::vector<Ref<Element>>>();
		XBDM::Console xbox = XboxManager::GetConsole();

		std::vector<XBDM::Drive> drives = xbox.GetDrives(&m_Success);

		if (m_Success)
		{
			for (auto& drive : drives)
				driveElements->emplace_back(CreateRef<Drive>(drive));

			ContentsChangeEvent event(driveElements);
			m_EventCallback(event);
		}
	}
}
