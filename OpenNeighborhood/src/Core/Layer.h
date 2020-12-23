#pragma once

#include "Core/Timestep.h"
#include "Events/Event.h"

class Layer
{
public:
	Layer(const std::string& name = "Layer") {}
	virtual ~Layer() {}

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(Timestep timestep) {}
	virtual void OnEvent(Event& event) {}
};
