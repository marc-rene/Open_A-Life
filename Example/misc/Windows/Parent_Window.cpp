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

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->WorkPos.x, ImGui::GetMainViewport()->WorkPos.y));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->WorkSize.x, ImGui::GetMainViewport()->WorkSize.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::Begin("PARENT_WINDOW___IGNORE", p_open, main_window_flags);                        
    ImGui::PopStyleVar();
    ImGui::End();

  
}