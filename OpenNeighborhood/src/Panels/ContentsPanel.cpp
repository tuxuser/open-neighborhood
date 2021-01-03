#include "pch.h"
#include "Panels/ContentsPanel.h"

#define MINI_CASE_SENSITIVE
#include <mINI/ini.h>

#include "Elements/AddXboxButton.h"
#include "Elements/Xbox.h"

ContentsPanel::ContentsPanel()
{
	m_Elements.emplace_back(CreateRef<AddXboxButton>());

	struct stat buffer;
	if (stat("OpenNeighborhood.ini", &buffer) != -1)
	{
		mINI::INIFile configFile("OpenNeighborhood.ini");
		mINI::INIStructure config;
		configFile.read(config);

		for (const auto& it : config)
		{
			const std::string& consoleName = it.first;
			if (config.get(consoleName).has("ip_address"))
			{
				std::string ipAddress = config.get(consoleName).get("ip_address");
				m_Elements.emplace_back(CreateRef<Xbox>(consoleName, ipAddress));
			}
		}
	}

	UpdateEventCallbacks();
}

void ContentsPanel::OnRender()
{
	float pathPanelSize = m_Margin * 5.0f;

	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(m_Margin, m_Margin * 2.0f + pathPanelSize));
	ImGui::SetNextWindowSize(ImVec2((float)m_WindowWidth - m_Margin * 2.0f, (float)m_WindowHeight - (m_Margin * 3.0f + pathPanelSize)));

	ImGui::Begin("Contents Window", nullptr, windowFlags);

	ImGuiStyle& style = ImGui::GetStyle();
	float panelWidth = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
	for (size_t i = 0; i < m_Elements.size(); i++)
	{
		ImGui::PushID((int)i);
		m_Elements[i]->OnRender();
		float lastButtonX = ImGui::GetItemRectMax().x;
		float nextButtonX = lastButtonX + style.ItemSpacing.x + m_Elements[i]->GetWidth(); // Expected position if next button was on same line
		if (i + 1 < m_Elements.size() && nextButtonX < panelWidth)
			ImGui::SameLine();
		ImGui::PopID();
	}

	ImGui::End();
}

void ContentsPanel::OnEvent(Event& event)
{
	Panel::OnEvent(event);

	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<ContentsChangeEvent>(BIND_EVENT_FN(ContentsPanel::OnContentsChange));
}

bool ContentsPanel::OnContentsChange(ContentsChangeEvent& event)
{
	if (event.Append())
	{
		m_Elements.reserve(m_Elements.size() + event.GetElements()->size());
		m_Elements.insert(m_Elements.end(), event.GetElements()->begin(), event.GetElements()->end());
	}
	else
		m_Elements = *event.GetElements();

	UpdateEventCallbacks();

	return true;
}

void ContentsPanel::UpdateEventCallbacks()
{
	for (auto& element : m_Elements)
		element->SetEventCallback(BIND_EVENT_FN(ContentsPanel::OnEvent));
}
