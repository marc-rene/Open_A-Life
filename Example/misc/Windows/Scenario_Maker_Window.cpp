#include "All_Windows.h"

void ImGui::Scenario_Maker_Window(bool* p_open)
{
    if (!ImGui::Begin("Scenario Maker", p_open))
    {
        ImGui::End();
        return;
    }

    
    
  

    ImGui::Text("Hello :D");

    ImGui::End();
}


