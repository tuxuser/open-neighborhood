#include "pch.h"

#include "OpenNeighborhoodApp.h"

int main()
{
	auto app = new OpenNeighborhoodApp();

	app->Run();

	delete app;
}
