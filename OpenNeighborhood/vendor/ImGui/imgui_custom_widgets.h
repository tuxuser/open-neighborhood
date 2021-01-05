#pragma once

#include "imgui.h"

namespace ImGui {
    IMGUI_API bool ImageButtonWithText(ImTextureID userTextureID, const ImVec2& imageSize, const ImVec2& totalSize, const char* label, const ImVec2& padding);
}
