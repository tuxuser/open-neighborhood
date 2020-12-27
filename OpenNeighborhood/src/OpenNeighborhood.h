#pragma once

#include "Core/Layer.h"
#include "Panels/MainPanel.h"
#include "Panels/PathPanel.h"

class OpenNeighborhood : public Layer
{
public:
	OpenNeighborhood();
	virtual ~OpenNeighborhood() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep timestep) override;
	virtual void OnEvent(Event& event) override;
private:
	MainPanel m_MainPanel;
	PathPanel m_PathPanel;
};
