#include "pch.h"
#include "Elements/Xbox.h"

#include "Render/TextureManager.h"
#include "Xbox/XboxManager.h"
#include "Events/AppEvent.h"
#include "Elements/Drive.h"

Xbox::Xbox(const std::string& label, const std::string& ipAddress)
	: m_IpAddress(ipAddress), Element(label, "xbox", 100.0f, 100.0f) {}

void Xbox::OnRender()
{
	bool success = true;

	if (ImGui::ImageButtonWithText((void*)(intptr_t)TextureManager::GetTexture(m_TextureName)->GetTextureID(), ImVec2(m_Width, m_Height), m_Label.c_str()))
	{
		std::string consoleName;
		success = XboxManager::CreateConsole(m_IpAddress, consoleName, true);

		if (success)
		{
			Ref<std::vector<Ref<Element>>> driveElements = CreateRef<std::vector<Ref<Element>>>();
			XBDM::Console xbox = XboxManager::GetConsole();
			
			std::vector<XBDM::Drive> drives = xbox.GetDrives(&success);

			if (success)
			{
				for (auto& drive : drives)
					driveElements->emplace_back(CreateRef<Drive>(drive));

				ContentsChangeEvent event(driveElements);
				m_EventCallback(event);
			}
		}
	}

	if (!success)
	{
		ImGui::OpenPopup("Connection failed!");

		ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	}

	if (ImGui::BeginPopupModal("Connection failed!", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Couldn't find console");

		if (ImGui::Button("OK", ImVec2(120, 0)))
			ImGui::CloseCurrentPopup();

		ImGui::EndPopup();
	}
}
