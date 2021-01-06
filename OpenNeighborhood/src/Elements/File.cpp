#include "pch.h"
#include "Elements/File.h"

File::File(const XBDM::FileEntry& data)
	: m_Data(data), Element(data.Name, data.IsDirectory ? "directory" : data.IsXEX ? "xex" : "file", "Couldn't access file!") {}

void File::OnClick()
{

}
