#include "All_Windows.h"
#include <nfd.h>
#include <stdlib.h>

void ImGui::Scenario_Maker_Window(bool* p_open)
{
    if (!ImGui::Begin("Scenario Maker", p_open))
    {
        ImGui::End();
        return;
    }

    NFD_Init();

    nfdu8char_t *outPath;
    nfdopendialogu8args_t args = {0};
    
    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
    if (result == NFD_OKAY)
    {
        puts("Success!");
        puts(outPath);
        NFD_FreePathU8(outPath);
    }
    else if (result == NFD_CANCEL)
    {
        puts("User pressed cancel.");
    }
    else 
    {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();
    
  

    ImGui::Text("Hello :D");

    ImGui::End();
}


