#pragma once

#include "Core/Core.h"
#include "Events/Event.h"
#include "Events/AppEvent.h"
#include "Core/Window.h"
#include "Core/Stack.h"
#include "Core/Layer.h"

class App
{
public:
	App(const std::string& name = "OpenNeighborhood");
	virtual ~App();

	void Run();

	void OnEvent(Event&);

	void PushLayer(Layer* layer);

	inline static App& Get() { return *s_Instance; }
	inline Window& GetWindow() { return *m_Window; }

	void Close();
private:
	Scope<Window> m_Window;
	bool m_Running = true;
	bool m_Minimized = false;

	Stack<Layer*> m_LayerStack;

	static App* s_Instance;

	bool OnWindowClose(WindowCloseEvent& event);
	bool OnWindowResize(WindowResizeEvent& event);
};
