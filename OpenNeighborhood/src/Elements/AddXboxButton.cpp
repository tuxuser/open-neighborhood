#include "pch.h"
#include "Elements/AddXboxButton.h"

#define MINI_CASE_SENSITIVE
#include <mINI/ini.h>

#include "Render/TextureManager.h"
#include "Xbox/XboxManager.h"
#include "Events/AppEvent.h"
#include "Elements/Xbox.h"

AddXboxButton::AddXboxButton() 
	: Element("Add Xbox 360", "addXboxButton", "Couldn't find console!") {}

void AddXboxButton::OnRender()
{
	auto texture = TextureManager::GetTexture(m_TextureName);

	if (ImGui::ImageButtonWithText((void*)(intptr_t)texture->GetTextureID(), ImVec2((float)texture->GetWidth(), (float)texture->GetHeight()), ImVec2((float)m_Width, (float)m_Height), m_Label.c_str(), ImVec2(m_Padding, m_Padding)))
		OnClick();

	ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginPopupModal("Add Xbox 360 ?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		static int bytes[4] = { 192, 168, 1, 100 };

		float width = ImGui::CalcItemWidth();
		ImGui::PushID("IP");
		ImGui::TextUnformatted("IP Address");
		ImGui::SameLine();
		for (int i = 0; i < 4; i++)
		{
			ImGui::PushItemWidth(width / 4.0f);
			ImGui::PushID(i);
			bool invalidByte = false;

			if (bytes[i] > 255)
			{
				// Make values over 255 red, and when focus is lost reset it to 255.
				bytes[i] = 255;
				invalidByte = true;
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			}
			else if (bytes[i] < 0)
			{
				// Make values below 0 yellow, and when focus is lost reset it to 0.
				bytes[i] = 0;
				invalidByte = true;
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
			}

			ImGui::InputInt("##v", &bytes[i], 0, 0, ImGuiInputTextFlags_CharsDecimal);

			if (invalidByte)
				ImGui::PopStyleColor();

			// Call ImGui::SameLine() only for the first 3 inputs
			if (i < 3)
				ImGui::SameLine();

			ImGui::PopID();
			ImGui::PopItemWidth();
		}

		ImGui::PopID();

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			std::stringstream ipAddress;
			ipAddress << bytes[0] << "." << bytes[1] << "." << bytes[2] << "." << bytes[3];
			
			std::string consoleName;
			m_Success = XboxManager::CreateConsole(ipAddress.str(), consoleName);

			if (m_Success)
				CreateXbox(consoleName, ipAddress.str());

			ImGui::CloseCurrentPopup();
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(120, 0)))
			ImGui::CloseCurrentPopup();

		ImGui::EndPopup();
	}

	if (!m_Success)
	{
		ImGui::OpenPopup("Connection failed!");

		ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	}

	if (ImGui::BeginPopupModal("Connection failed!", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text(m_ErrorMessage.c_str());

		if (ImGui::Button("OK", ImVec2(120, 0)))
			ImGui::CloseCurrentPopup();

		ImGui::EndPopup();
	}

	ImGui::ShowDemoWindow();
}

void AddXboxButton::OnClick()
{
	ImGui::OpenPopup("Add Xbox 360 ?");
}

void AddXboxButton::CreateXbox(const std::string& consoleName, const std::string& ipAddress)
{
	Ref<std::vector<Ref<Element>>> xboxElement = CreateRef<std::vector<Ref<Element>>>();
	xboxElement->emplace_back(CreateRef<Xbox>(consoleName, ipAddress));
	ContentsChangeEvent event(xboxElement, true);
	m_EventCallback(event);

	mINI::INIFile configFile("OpenNeighborhood.ini");
	mINI::INIStructure config;

	struct stat buffer;
	if (stat("OpenNeighborhood.ini", &buffer) == -1)
	{
		config[consoleName]["ip_address"] = ipAddress;
		configFile.generate(config, true);
	}
	else
	{
		configFile.read(config);
		config[consoleName]["ip_address"] = ipAddress;
		configFile.write(config, true);
	}
}
