#include "imgui.h"
#include "imgui_internal.h"


//-----------------------------------------------------------------------------
// [SECTION] Style functions
//-----------------------------------------------------------------------------

static ImVec4 Primary;
static ImVec4 PrimaryOff;
static ImVec4 Secondary;
static ImVec4 SecondaryOff;
static ImVec4 Font;
static ImVec4 Accent(0.92f, 0.18f, 0.29f, 0.70f); // #eb2e4a
static ImVec4 Accent_lighten(Accent);
static ImVec4 Accent_darken(Accent);

static ImVec4 Success(Accent);
static ImVec4 DangerColour(1.0f, 0.835f, 0.278f, 1.00f);
static ImVec4 WarningColour(0.28f, 0.37f, 1.00f, 1.00f);
static ImVec4 CoolColour(0.408f, 0.439f, 0.667f, 1.00f);

namespace ImGui
{
    // Styles
    IMGUI_API void SetStyleMode(ImGuiStyle* dst = nullptr, bool useDarkMode = true);
}
