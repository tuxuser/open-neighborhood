#pragma once

class UI
{
public:
	static void Init();

	static void BeginFrame();
	static void EndFrame();

	static void Cleanup();
private:
	static void SetDarkThemeColors();
};
