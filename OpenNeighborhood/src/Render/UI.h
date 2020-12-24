#pragma once

class UI
{
public:
	static void Init();

	static void Render();

	static void Cleanup();
private:
	static void BeginFrame();
	static void EndFrame();

	static void SetDarkThemeColors();
};
