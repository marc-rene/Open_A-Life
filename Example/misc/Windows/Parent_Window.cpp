#include "All_Windows.h"
#include "Styles/custom_styles.h"

void ImGui::Parent_Window(bool* p_open)
{
    ImGuiWindowFlags main_window_flags = 0;
    main_window_flags |= ImGuiWindowFlags_NoTitleBar;
    main_window_flags |= ImGuiWindowFlags_NoMove;
    main_window_flags |= ImGuiWindowFlags_NoNav;
    main_window_flags |= ImGuiWindowFlags_NoResize;
    main_window_flags |= ImGuiWindowFlags_NoCollapse;
    main_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    SetNextWindowPos(ImVec2(GetMainViewport()->WorkPos.x, GetMainViewport()->WorkPos.y));
    SetNextWindowSize(ImVec2(GetMainViewport()->WorkSize.x, GetMainViewport()->WorkSize.y));
    PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    Begin("PARENT_WINDOW___IGNORE", p_open, main_window_flags);
    PopStyleVar();
    End();
}
