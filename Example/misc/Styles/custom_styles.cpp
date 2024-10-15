#include "imgui.h"
#include "imgui_internal.h"
#include "custom_styles.h"


//-----------------------------------------------------------------------------
// [SECTION] Style functions
//-----------------------------------------------------------------------------



static ImVec4 Primary;
static ImVec4 Secondary;
static ImVec4 Font;
static ImVec4 Accent            (0.92f, 0.18f, 0.29f, 0.70f);
static ImVec4 Accent_lighten    (Accent);
static ImVec4 Accent_darken     (Accent);
static ImVec4 Important         (0.78f, 0.18f, 0.92f, 1.00f);




// FIX
void ImGui::SetStyleMode(ImGuiStyle* dst, bool useDarkMode)
{
    ImVec4* c = ImGui::GetStyle().Colors;
    
    // - - - - - - - - - - - - - - - - - - - - - - -    DARK MODE - - - - - - - - - | - - - LIGHT MODE - - - - - -   
    Primary = useDarkMode ?                     ImVec4(0.13f, 0.14f, 0.17f, 1.00f)  : ImVec4(0.92f, 0.91f, 0.88f, 0.70f);
    Secondary = useDarkMode ?                   ImVec4(0.20f, 0.22f, 0.27f, 1.00f)  : ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    Font = useDarkMode ?                        ImVec4(0.90f, 0.94f, 0.91f, 1.00f)  : ImVec4(0.20f, 0.29f, 0.28f, 1.00f);
    Accent_lighten.w    = useDarkMode ? 1.00f : 0.45f;
    Accent_darken.w     = useDarkMode ? 0.45f : 1.00f;

    c[ImGuiCol_Text] = Font;    
    c[ImGuiCol_TextDisabled] = useDarkMode ?    ImVec4(0.86f, 0.93f, 0.89f, 0.28f)  : ImVec4(0.40f, 0.39f, 0.38f, 0.77f);    
    c[ImGuiCol_WindowBg] = Primary;    
    c[ImGuiCol_PopupBg] = Secondary;    
    c[ImGuiCol_Border] = Accent;    
    c[ImGuiCol_BorderShadow] = Secondary;    
    c[ImGuiCol_FrameBg] = Secondary;    
    c[ImGuiCol_FrameBgHovered] = Accent;    
    c[ImGuiCol_FrameBgActive] = Secondary;   
    c[ImGuiCol_Tab] = Primary;
    c[ImGuiCol_TabSelected] = Accent;
    c[ImGuiCol_TabHovered] = Secondary;
    c[ImGuiCol_TabDimmed] = Primary;
    c[ImGuiCol_TabSelectedOverline] = Important;
    c[ImGuiCol_TabDimmedSelected] = Secondary;
    c[ImGuiCol_TitleBg] = Primary;    
    c[ImGuiCol_TitleBgCollapsed] = Secondary;    
    c[ImGuiCol_TitleBgActive] = Secondary;    
    c[ImGuiCol_MenuBarBg] = Accent;    
    c[ImGuiCol_ScrollbarBg] = Primary;    
    c[ImGuiCol_ScrollbarGrab] = Accent_darken;    
    c[ImGuiCol_ScrollbarGrabHovered] = Accent;    
    c[ImGuiCol_ScrollbarGrabActive] = Accent_lighten;    
    c[ImGuiCol_SliderGrab] = Accent;    
    c[ImGuiCol_SliderGrabActive] = Accent_darken;    
    c[ImGuiCol_Button] = Accent_lighten;    
    c[ImGuiCol_ButtonHovered] = Accent;    
    c[ImGuiCol_ButtonActive] = Accent_darken;    
    c[ImGuiCol_ResizeGrip] = Accent;
    c[ImGuiCol_ResizeGripHovered] = Accent_lighten;
    c[ImGuiCol_ResizeGripActive] = Accent_darken;
    c[ImGuiCol_PlotLines] = useDarkMode ?       ImVec4(0.86f, 0.93f, 0.89f, 0.63f) : ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    c[ImGuiCol_PlotLinesHovered] = useDarkMode? ImVec4(0.92f, 0.18f, 0.29f, 1.00f) : ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    c[ImGuiCol_PlotHistogram] = useDarkMode ?   ImVec4(0.86f, 0.93f, 0.89f, 0.63f) : ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    c[ImGuiCol_PlotHistogramHovered] = useDarkMode ? ImVec4(0.92f, 0.18f, 0.29f, 1.00f) : ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    c[ImGuiCol_TextSelectedBg] = Accent_lighten;
    c[ImGuiCol_HeaderHovered] = Accent; 
    c[ImGuiCol_HeaderActive] = Accent_darken;
    c[ImGuiCol_CheckMark]              = Accent;    
    c[ImGuiCol_Header]                 = Accent_lighten;
    c[ImGuiCol_DockingPreview] = Important;
    c[ImGuiCol_Separator]              = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);   // Unsure, fix later
    c[ImGuiCol_SeparatorHovered]       = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);   // Unsure, fix later
    c[ImGuiCol_SeparatorActive]        = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);   // Unsure, fix later
}
