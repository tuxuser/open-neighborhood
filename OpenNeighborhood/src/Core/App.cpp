#include "pch.h"
#include "Core/App.h"

App* App::s_Instance = nullptr;

App::App(const std::string& name)
{
	ASSERT(!s_Instance, "App already exists!");
	s_Instance = this;

	m_Window = Scope<Window>(Window::Create(WindowProps(name)));
	m_Window->SetEventCallback(BIND_EVENT_FN(App::OnEvent));
}

App::~App() {}

void App::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void App::Close()
{
	m_Running = false;
}

void App::Run()
{
	while (m_Running)
	{
		Timestep ts;

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate(ts);

		m_Window->OnUpdate();
	}
}

void App::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClose));

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.m_Handled)
			break;
	}
}

bool App::OnWindowClose(WindowCloseEvent& e)
{
	Close();
	return true;
}

bool App::OnWindowResize(WindowResizeEvent& e)
{
	if (e.GetWidth() == 0 || e.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}

	m_Minimized = false;

	return false;
}
