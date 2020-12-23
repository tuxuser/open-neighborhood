#include "pch.h"

#include "Core/App.h"

int main()
{
	auto app = new App();

	app->Run();

	delete app;
}
