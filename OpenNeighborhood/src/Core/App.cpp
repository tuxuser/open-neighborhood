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

App::~App()
{
	for (Layer* layer : m_LayerStack)
		layer->OnDetach();
}

void App::PushLayer(Layer* layer)
{
	m_LayerStack.Push(layer);
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

void App::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClose));

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(event);
		if (event.m_Handled)
			break;
	}
}

bool App::OnWindowClose(WindowCloseEvent& event)
{
	Close();
	return true;
}

bool App::OnWindowResize(WindowResizeEvent& event)
{
	if (event.GetWidth() == 0 || event.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}

	m_Minimized = false;

	return false;
}
