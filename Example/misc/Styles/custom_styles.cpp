#include "imgui.h"
#include "imgui_internal.h"
#include "custom_styles.h"


//-----------------------------------------------------------------------------
// [SECTION] Style functions
//-----------------------------------------------------------------------------


void ImGui::SetStyleMode(ImGuiStyle* dst, bool useDarkMode)
{
    ImVec4* c = GetStyle().Colors;

    GetStyle().WindowPadding = ImVec2(15, 15);
    GetStyle().WindowRounding = 10.0f;
    GetStyle().FrameRounding = 4.0f;
    GetStyle().ItemSpacing = ImVec2(12, 8);
    GetStyle().ItemInnerSpacing = ImVec2(8, 6);
    GetStyle().IndentSpacing = 25.0f;
    GetStyle().ScrollbarSize = 15.0f;
    GetStyle().ScrollbarRounding = 9.0f;
    GetStyle().GrabRounding = 3.0f;
    GetStyle().SeparatorTextPadding = ImVec2(25.0f, 5.0f);


    // - - - - - - - - - - - - - - - - - - - - - - -    DARK MODE - - - - - - - - - | - - - LIGHT MODE - - - - - -   
    constexpr float slight_offset = 1.3f;
    Primary = useDarkMode ? ImVec4(0.13f, 0.14f, 0.17f, 1.00f) : ImVec4(0.93f, 0.93f, 0.96f, 1.00f);
    PrimaryOff = ImVec4(Primary.x * slight_offset, Primary.y * slight_offset, Primary.z * slight_offset, Primary.w);
    Secondary = useDarkMode ? ImVec4(0.20f, 0.22f, 0.27f, 1.00f) : ImVec4(0.70f, 0.72f, 0.77f, 1.00f);
    SecondaryOff = ImVec4(Secondary.x * slight_offset, Secondary.y * slight_offset, Secondary.z * slight_offset,
                          Secondary.w);
    Font = useDarkMode ? ImVec4(0.90f, 0.94f, 0.91f, 1.00f) : ImVec4(0.20f, 0.29f, 0.28f, 1.00f);
    Accent_lighten.w = useDarkMode ? 0.90f : 0.45f;
    Accent_darken.w = useDarkMode ? 0.45f : 0.90f;

    c[ImGuiCol_Text] = Font;
    c[ImGuiCol_TextDisabled] = useDarkMode ? ImVec4(0.86f, 0.93f, 0.89f, 0.28f) : ImVec4(0.40f, 0.39f, 0.38f, 0.77f);
    c[ImGuiCol_WindowBg] = Primary;
    c[ImGuiCol_PopupBg] = Secondary;
    c[ImGuiCol_Border] = Accent;
    c[ImGuiCol_BorderShadow] = Secondary;
    c[ImGuiCol_FrameBg] = Secondary;
    c[ImGuiCol_FrameBgHovered] = Accent_darken;
    c[ImGuiCol_FrameBgActive] = Accent_lighten;
    c[ImGuiCol_Tab] = PrimaryOff;
    c[ImGuiCol_TabSelected] = Accent;
    c[ImGuiCol_TabHovered] = Accent_lighten;
    c[ImGuiCol_TabDimmed] = Primary;
    c[ImGuiCol_TabDimmedSelected] = Accent;
    c[ImGuiCol_TabDimmedSelectedOverline] = Secondary;
    c[ImGuiCol_TitleBg] = useDarkMode ? Primary : Secondary;
    c[ImGuiCol_TitleBgCollapsed] = Secondary;
    c[ImGuiCol_TitleBgActive] = useDarkMode ? Secondary : Primary;
    c[ImGuiCol_TabSelectedOverline] = c[ImGuiCol_TitleBgActive];
    c[ImGuiCol_MenuBarBg] = Accent;
    c[ImGuiCol_ScrollbarBg] = Primary;
    c[ImGuiCol_ScrollbarGrab] = Accent_darken;
    c[ImGuiCol_ScrollbarGrabHovered] = Accent;
    c[ImGuiCol_ScrollbarGrabActive] = Accent_lighten;
    c[ImGuiCol_SliderGrab] = Accent;
    c[ImGuiCol_SliderGrabActive] = Secondary;
    c[ImGuiCol_Button] = Accent_lighten;
    c[ImGuiCol_ButtonHovered] = Accent;
    c[ImGuiCol_ButtonActive] = Accent_darken;
    c[ImGuiCol_ResizeGrip] = Accent;
    c[ImGuiCol_ResizeGripHovered] = Accent_lighten;
    c[ImGuiCol_ResizeGripActive] = Accent_darken;
    c[ImGuiCol_PlotLines] = useDarkMode ? ImVec4(0.86f, 0.93f, 0.89f, 0.63f) : ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    c[ImGuiCol_PlotLinesHovered] =
        useDarkMode ? ImVec4(0.92f, 0.18f, 0.29f, 1.00f) : ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    c[ImGuiCol_PlotHistogram] = useDarkMode ? ImVec4(0.86f, 0.93f, 0.89f, 0.63f) : ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    c[ImGuiCol_PlotHistogramHovered] = useDarkMode
                                           ? ImVec4(0.92f, 0.18f, 0.29f, 1.00f)
                                           : ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    c[ImGuiCol_TextSelectedBg] = Accent_lighten;
    c[ImGuiCol_HeaderHovered] = Accent;
    c[ImGuiCol_HeaderActive] = Accent_darken;
    c[ImGuiCol_CheckMark] = Accent;
    c[ImGuiCol_Header] = Accent_lighten;
    c[ImGuiCol_DockingPreview] = Accent;
    c[ImGuiCol_Separator] = SecondaryOff; // Unsure, fix later
    c[ImGuiCol_SeparatorHovered] = Accent_darken; // Unsure, fix later
    c[ImGuiCol_SeparatorActive] = Accent_lighten; // Unsure, fix later
    c[ImGuiCol_TableHeaderBg] = useDarkMode ? Accent_darken : Accent_lighten;
    c[ImGuiCol_TableBorderStrong] = ImVec4(Font.x, Font.y, Font.z, 0.4f);
    c[ImGuiCol_TableBorderLight] = ImVec4(Font.x, Font.y, Font.z, 0.5f);
}
