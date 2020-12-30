#include "pch.h"
#include "Elements/AddXboxButton.h"

#include "Render/TextureManager.h"
#include "Xbox/XboxManager.h"

AddXboxButton::AddXboxButton() 
	: Element("Add Xbox 360", "addXboxButton") {}

void AddXboxButton::OnRender()
{
	if (ImGui::ImageButtonWithText((void*)(intptr_t)TextureManager::GetTexture(m_TextureName)->GetTextureID(), ImVec2(100.0f, 100.0f), m_Label.c_str()))
		ImGui::OpenPopup("Add Xbox 360 ?");

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
			
			AddXbox(ipAddress.str());

			ImGui::CloseCurrentPopup();
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(120, 0)))
			ImGui::CloseCurrentPopup();

		ImGui::EndPopup();
	}
}

void AddXboxButton::AddXbox(const std::string& ipAddress)
{
	XboxManager::CreateConsole(ipAddress);
}