#include "imgui.h"
#include "imgui_internal.h"
#include "custom_styles.h"


//-----------------------------------------------------------------------------
// [SECTION] Style functions
//-----------------------------------------------------------------------------



static ImVec4 Primary;
static ImVec4 Secondary;
static ImVec4 Text;
static ImVec4 Text_disabled;
static ImVec4 Accent            (0.92f, 0.18f, 0.29f, 0.70f);
static ImVec4 Accent_lighten    (Accent);
static ImVec4 Accent_darken     (Accent);




// FIX
void ImGui::SetStyleMode(ImGuiStyle* dst, bool useDarkMode)
{
    ImVec4* c = ImGui::GetStyle().Colors;
    
    // - - - - - - - - - - - - - - - - - - - - - - -    DARK MODE - - - - - - - - | - - - LIGHT MODE - - - - - -   
    Primary = useDarkMode ?                     ImVec4(0.13f, 0.14f, 0.17f, 1.0f) : ImVec4(1.00f, 0.91f, 0.82f, 1.0f);
    Secondary = useDarkMode ?                   ImVec4(0.20f, 0.22f, 0.27f, 1.0f) : ImVec4(1.00f, 0.82f, 0.61f, 1.0f);
    
    Accent_lighten.w    = useDarkMode ? 1.00f : 0.45f;
    Accent_darken.w     = useDarkMode ? 0.45f : 1.00f;

    c[ImGuiCol_Text] = useDarkMode ?            ImVec4(0.40f, 0.39f, 0.38f, 1.00f) : ImVec4(0.86f, 0.93f, 0.89f, 0.78f);    
    c[ImGuiCol_TextDisabled] = useDarkMode ?    ImVec4(0.40f, 0.39f, 0.38f, 0.77f) : ImVec4(0.86f, 0.93f, 0.89f, 0.28f);    
    c[ImGuiCol_WindowBg] = useDarkMode?         ImVec4(0.92f, 0.91f, 0.88f, 0.70f) : ImVec4(0.13f, 0.14f, 0.17f, 1.00f);    
    c[ImGuiCol_PopupBg] = useDarkMode ?         ImVec4(0.92f, 0.91f, 0.88f, 0.92f) : ImVec4(0.20f, 0.22f, 0.27f, 0.90f);    
    c[ImGuiCol_Border] = useDarkMode ?          ImVec4(0.84f, 0.83f, 0.80f, 0.65f) : ImVec4(0.31f, 0.31f, 1.00f, 0.00f);    
    c[ImGuiCol_BorderShadow] = useDarkMode ?    ImVec4(0.92f, 0.91f, 0.88f, 0.00f) : ImVec4(0.00f, 0.00f, 0.00f, 0.00f);    
    c[ImGuiCol_FrameBg] = useDarkMode ?         ImVec4(1.00f, 0.98f, 0.95f, 1.00f) : ImVec4(0.20f, 0.22f, 0.27f, 1.00f);    
    c[ImGuiCol_FrameBgHovered] = useDarkMode ?  ImVec4(0.99f, 1.00f, 0.40f, 0.78f) : ImVec4(0.92f, 0.18f, 0.29f, 0.78f);    
    c[ImGuiCol_FrameBgActive] = useDarkMode ?   ImVec4(0.26f, 1.00f, 0.00f, 1.00f) : ImVec4(0.92f, 0.18f, 0.29f, 1.00f);    
    c[ImGuiCol_TitleBg] = useDarkMode ?         ImVec4(1.00f, 0.98f, 0.95f, 1.00f) : ImVec4(0.20f, 0.22f, 0.27f, 1.00f);    
    c[ImGuiCol_TitleBgCollapsed] = useDarkMode? ImVec4(1.00f, 0.98f, 0.95f, 0.75f) : ImVec4(0.20f, 0.22f, 0.27f, 0.75f);    
    c[ImGuiCol_TitleBgActive] = useDarkMode ?   ImVec4(0.25f, 1.00f, 0.00f, 1.00f) : ImVec4(0.92f, 0.18f, 0.29f, 1.00f);    
    c[ImGuiCol_MenuBarBg] = useDarkMode ?       ImVec4(1.00f, 0.98f, 0.95f, 0.47f) : ImVec4(0.20f, 0.22f, 0.27f, 0.47f);    
    c[ImGuiCol_ScrollbarBg] = useDarkMode ?     ImVec4(1.00f, 0.98f, 0.95f, 1.00f) : ImVec4(0.20f, 0.22f, 0.27f, 1.00f);    
    c[ImGuiCol_ScrollbarGrab] = useDarkMode ?   ImVec4(0.00f, 0.00f, 0.00f, 0.21f) : ImVec4(0.09f, 0.15f, 0.16f, 1.00f);    
    c[ImGuiCol_ScrollbarGrabHovered] = useDarkMode ? ImVec4(0.90f, 0.91f, 0.00f, 0.78f) : ImVec4(0.92f, 0.18f, 0.29f, 0.78f);    
    c[ImGuiCol_ScrollbarGrabActive] = useDarkMode ? ImVec4(0.25f, 1.00f, 0.00f, 1.00f) : ImVec4(0.92f, 0.18f, 0.29f, 1.00f);    
    c[ImGuiCol_SliderGrab] = useDarkMode ?      ImVec4(0.00f, 0.00f, 0.00f, 0.14f) : ImVec4(0.47f, 0.77f, 0.83f, 0.14f);    
    c[ImGuiCol_SliderGrabActive] = useDarkMode? ImVec4(0.25f, 1.00f, 0.00f, 1.00f) : ImVec4(0.92f, 0.18f, 0.29f, 1.00f);    
    c[ImGuiCol_Button] = useDarkMode ?          ImVec4(0.00f, 0.00f, 0.00f, 0.14f) : ImVec4(0.47f, 0.77f, 0.83f, 0.14f);    
    c[ImGuiCol_ButtonHovered] = useDarkMode ?   ImVec4(0.99f, 1.00f, 0.22f, 0.86f) : ImVec4(0.92f, 0.18f, 0.29f, 0.86f);    
    c[ImGuiCol_ButtonActive] = useDarkMode ?    ImVec4(0.25f, 1.00f, 0.00f, 1.00f) : ImVec4(0.92f, 0.18f, 0.29f, 1.00f);    
    c[ImGuiCol_HeaderHovered] = Accent;
    c[ImGuiCol_HeaderActive] = Accent_darken;
    c[ImGuiCol_ResizeGrip] = useDarkMode ?      ImVec4(0.00f, 0.00f, 0.00f, 0.04f) : ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    c[ImGuiCol_ResizeGripHovered] = useDarkMode ? ImVec4(0.25f, 1.00f, 0.00f, 0.78f) : ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    c[ImGuiCol_ResizeGripActive] = useDarkMode ? ImVec4(0.25f, 1.00f, 0.00f, 1.00f) : ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    c[ImGuiCol_PlotLines] = useDarkMode ?       ImVec4(0.40f, 0.39f, 0.38f, 0.63f) : ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
    c[ImGuiCol_PlotLinesHovered] = useDarkMode? ImVec4(0.25f, 1.00f, 0.00f, 1.00f) : ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    c[ImGuiCol_PlotHistogram] = useDarkMode ?   ImVec4(0.40f, 0.39f, 0.38f, 0.63f) : ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
    c[ImGuiCol_PlotHistogramHovered] = useDarkMode ? ImVec4(0.25f, 1.00f, 0.00f, 1.00f) : ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    c[ImGuiCol_TextSelectedBg] = useDarkMode ?  ImVec4(0.25f, 1.00f, 0.00f, 0.43f) : ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
    c[ImGuiCol_CheckMark]              = Accent;    
    c[ImGuiCol_Header]                 = Accent_darken;
    c[ImGuiCol_Separator]              = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);   // Unsure, fix later
    c[ImGuiCol_SeparatorHovered]       = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);   // Unsure, fix later
    c[ImGuiCol_SeparatorActive]        = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);   // Unsure, fix later
}
