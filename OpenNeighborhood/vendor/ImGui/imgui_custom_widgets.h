#pragma once

#include "imgui.h"

namespace ImGui {
    IMGUI_API bool ImageButtonWithText(ImTextureID user_texture_id, const ImVec2& size, const char* label, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));
}
