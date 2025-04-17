#include "All_Windows.h"
#include "IMGUI_TEST/imgui_filebrowser.h"

void ImGui::Scenario_Maker_Window(bool* p_open)
{
    if (!ImGui::Begin("Scenario Maker", p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::Button("Pick file"))
        ImGui::OpenFileBrowser("C:\\Other\\Git\\Open_A-Life\\Example");

    std::string result;
    
    
  

    ImGui::Text("Hello :D");

    ImGui::End();
}


