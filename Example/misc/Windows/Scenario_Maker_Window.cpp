#include "All_Windows.h"


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
// Windows code here 
#include <commdlg.h>
#else
// Linux Code here
#endif

auto Window_Title = "Scenario Maker";

std::filesystem::path GetNewScenarioPath()
{
    auto scenario_file_path = A_LIFE::File_Wizard::SetSavePath(
        "Scenario Files (*.scenario)\0*.scenario\0All Files (*.*)\0*.*\0",
        "scenario",
        "Untitled Scene",
        "Habibi, where we save our new Scenario?");
    bool file_exists = A_LIFE::File_Wizard::Does_INI_Exist(scenario_file_path, true);
    if (file_exists)
    {
        INFO(Window_Title, "New Scenario File is at {}", scenario_file_path.string());
        return scenario_file_path;
    }
    WARN(Window_Title, "Scenario File does not exist");
    return std::filesystem::current_path() / "Untitled.scenario";
}

void ImGui::Scenario_Maker_Window(bool* p_open)
{
    static std::filesystem::path scenario_file_path;

    if (!Begin(Window_Title, p_open))
    {
        End();
        return;
    }
    bool finished = false;

    if (scenario_file_path.empty() || Button("Change Save Location"))
    {
        scenario_file_path = GetNewScenarioPath();
    }

    static mINI::INIFile file(scenario_file_path.string());
    static mINI::INIStructure scenario_settings;

    SameLine();
    Text("Scenario Save path: %s", scenario_file_path.string().c_str());
    scenario_settings["VERSION"]["A-LIFE version"] = LOCAL_ALIFE_VERSION.to_string();
    scenario_settings["VERSION"]["A-LIFE full title"] = LOCAL_ALIFE_VERSION.full_title();

    SeparatorText("Basic");
    static char scenario_name[256] = "";
    InputTextWithHint("Scenario name", "\"Star Wars without Vader\"", scenario_name, 256);
    scenario_settings["MAIN"]["Scenario name"] = scenario_name;


    if (BeginTable("spacingTable", 4))
    {
        TableNextRow();
        TableSetColumnIndex(3);
        if (Button("Create new Scenario") && A_LIFE::File_Wizard::Prompt_Confirm("Create new Scenario",
                                                                                 "Are you sure you would like to\ncreate a new Scenario file?"))
        {
            file.write(scenario_settings, true);
            finished = true;
        }
        EndTable();
    }

    End();
    // !!!!!!!!!!!!!!!!!!!!!!!
    // THIS WILL CAUSE CHAOS
    if (finished)
        *p_open = false;
    // !!!!!!!!!!!!!!!!!!!!!!!
}
