#include "CreateWindow.h"
#include "Windows/All_Windows.h"
#include "Open_ALife.h"

// Main code
int main(int, char**)
{
    ALIFE_SCENARIO ExampleCore;
    ExampleCore.Init();
    //ExampleCore.Director = ALIFE_CoreObject("Director");
    //ExampleCore.Packet_Ninja = ALIFE_CoreObject("Packet Ninja");

    CreateAppWindow(&ExampleCore);
    
    return 0;
}


