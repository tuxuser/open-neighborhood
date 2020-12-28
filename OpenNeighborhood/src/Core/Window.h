#pragma once

#include <GLFW/glfw3.h>

#include "Core/Core.h"
#include "Events/Event.h"

struct WindowProps
{
	std::string title;
	uint32_t width;
	uint32_t height;

	WindowProps(const std::string& title = "OpenNeighborhood",
		uint32_t width = 1280,
		uint32_t height = 720)
		: title(title), width(width), height(height) {}
};

class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	Window(const WindowProps& props);
	virtual ~Window();

	void OnUpdate();

	inline unsigned int GetWidth() const { return m_Data.width; }
	inline unsigned int GetHeight() const { return m_Data.height; }

	// Window attributes
	inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.eventCallback = callback; }
	void SetVSync(bool enabled);
	bool IsVSync() const;

	inline void* GetNativeWindow() const { return m_Window; }

	static Window* Create(const WindowProps& props = WindowProps());
private:
	GLFWwindow* m_Window;

	struct WindowData
	{
		std::string title;
		unsigned int width, height;
		bool VSync;

		EventCallbackFn eventCallback;
	};

	WindowData m_Data;

	void Init(const WindowProps& props);
	void Shutdown();
};
