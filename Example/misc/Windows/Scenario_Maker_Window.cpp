#include "All_Windows.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
// Windows code here
#else
// Linux Code here
#endif

static std::filesystem::path SetSavePath();

void ImGui::Scenario_Maker_Window(bool* p_open)
{
    static std::filesystem::path scenario_file_path;
    if (!ImGui::Begin("Scenario Maker", p_open))
    {
        ImGui::End();
        return;
    }

    if (scenario_file_path.empty())
    {
        scenario_file_path = SetSavePath();
        INFO("Scenario Maker Window", "First time running, save path is set to {}", scenario_file_path.string());
    }
    
  

    ImGui::Text("Hello :D");

    ImGui::End();
}


std::filesystem::path SetSavePath()
{
    return std::filesystem::current_path();
}