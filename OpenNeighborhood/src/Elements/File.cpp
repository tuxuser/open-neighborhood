#include "pch.h"
#include "Elements/File.h"

#include "Xbox/XboxManager.h"
#include "Events/AppEvent.h"

File::File(const XBDM::FileEntry& data)
	: m_Data(data), Element(data.Name, data.IsDirectory ? "directory" : data.IsXEX ? "xex" : "file", "Couldn't access file!") {}

void File::OnClick()
{
	if (m_Data.IsDirectory)
		OpenDirectory();
}

void File::OpenDirectory()
{
	XBDM::Console xbox = XboxManager::GetConsole();
	std::vector<XBDM::FileEntry> files = xbox.GetDirectoryContents(XboxManager::GetCurrentLocation() + '\\' + m_Data.Name, &m_Success);

	if (m_Success)
	{
		Ref<std::vector<Ref<Element>>> fileElements = CreateRef<std::vector<Ref<Element>>>();

		for (auto& file : files)
			fileElements->emplace_back(CreateRef<File>(file));

		ContentsChangeEvent event(fileElements);
		m_EventCallback(event);

		XboxManager::GoToDirectory(m_Data.Name);
	}
}
