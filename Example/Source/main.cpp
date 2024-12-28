#include "CreateWindow.h"
#include "Windows/All_Windows.h"
#include "Core/Core.h"

// Main code
int main(int, char**)
{
    ALIFE_PAIRING ExampleCore;
    ExampleCore.Director = ALIFE_CoreObject("Director");
    ExampleCore.Packet_Ninja = ALIFE_CoreObject("Packet Ninja");

    CreateAppWindow(&ExampleCore);
    
    return 0;
}


