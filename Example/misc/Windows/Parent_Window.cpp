#include "All_Windows.h"
#include "Styles/custom_styles.h"

void ImGui::Parent_Window(bool* p_open, networking_settings* nSettings )
{
    ImGuiWindowFlags main_window_flags = 0;
    main_window_flags |= ImGuiWindowFlags_NoTitleBar;
    //main_window_flags |= ImGuiWindowFlags_MenuBar;
    main_window_flags |= ImGuiWindowFlags_NoMove;
    main_window_flags |= ImGuiWindowFlags_NoResize;
    main_window_flags |= ImGuiWindowFlags_NoCollapse;
    main_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;


    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y));
    ImGui::SetNextWindowSize(ImVec2(main_viewport->WorkSize.x, main_viewport->WorkSize.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::Begin("Hello world again!", p_open, main_window_flags);                          // Create a window called "Hello, world!" and append into it.
    
    // - - - This is where the fun begins! - - - - - - - - - - - - - - - - - - - - -

    // Top Menu 
    
    if(ImGui::BeginMainMenuBar())
    {
        // Networking
        if (ImGui::BeginMenu("Networking"))
        {
            
            static char status_text[32];
            
            //if (nSettings->is_listening()) {
                sprintf(status_text, "Port: %d", nSettings->listening_port);
                ImGui::MenuItem(status_text, NULL, false, false);
            /* }
            else {
                ImGui::PushStyleColor(ImGuiCol_Text, Success);
                ImGui::MenuItem("Not Connected", NULL, false, false);
                ImGui::PopStyleColor();
            }*/
            ImGui::Separator();
            ImGui::MenuItem("Listen on port");

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

     


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            
    ImGui::PopStyleVar();
    ImGui::End();
}