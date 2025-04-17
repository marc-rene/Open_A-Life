#include "All_Windows.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
// Windows code here 
#include <commdlg.h>
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

    ImGui::Text("Current Save path is {}", scenario_file_path.string());

    ImGui::End();
}


std::filesystem::path SetSavePath()
{
    char szFile[MAX_PATH] = { 0 };

    OPENFILENAMEA ofn = { 0 };
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Scenario Files (*.scenario)\0*.scenario\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "scenario";
    ofn.lpTemplateName = "Salut maman";
    ofn.lpstrTitle = "Habibi, where we save our new Scenario?";

    if (GetSaveFileNameA(&ofn)) {
        return std::filesystem::path(ofn.lpstrFile);
    }
    else {
        // User cancelled or an error occurred
        return std::filesystem::current_path() / "Nouveau Scenario.scenario";
    }
}