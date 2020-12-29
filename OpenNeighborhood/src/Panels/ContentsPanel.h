#pragma once

#include "Panels/Panel.h"
#include "Events/AppEvent.h"
#include "Render/Texture.h"

class ContentsPanel : public Panel
{
public:
	ContentsPanel();

	virtual void OnRender() override;
private:
	std::unordered_map<std::string, Ref<Texture>> m_Textures;
	uint32_t m_TextureCount = 0;
};
