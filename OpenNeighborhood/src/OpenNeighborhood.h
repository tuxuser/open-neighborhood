#pragma once

#include "Core/Layer.h"

class OpenNeighborhood : public Layer
{
public:
	OpenNeighborhood();
	virtual ~OpenNeighborhood() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep timestep) override;
	virtual void OnEvent(Event& event) override;
};
