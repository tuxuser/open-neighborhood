#pragma once

#include "Core/App.h"
#include "OpenNeighborhood.h"

class OpenNeighborhoodApp : public App
{
public:
	OpenNeighborhoodApp()
	{
		PushLayer(new OpenNeighborhood());
	}

	~OpenNeighborhoodApp() {}
};
