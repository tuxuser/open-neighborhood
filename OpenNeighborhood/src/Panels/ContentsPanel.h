#pragma once

#include "Panels/Panel.h"
#include "Events/AppEvent.h"
#include "Render/Texture.h"

class ContentsPanel : public Panel
{
public:
	ContentsPanel();

	virtual void OnRender() override;
};
