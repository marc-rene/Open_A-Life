#include "CreateWindow.h"
#include "Windows/All_Windows.h"

// Main code
int main(int, char**)
{
    A_LIFE::ALIFE_SCENARIO ExampleCore;
    //INFOc("Hello AGAIN!!!");
    INFOc(SUCCESS_msg);
    //ExampleCore.Init();
    //ExampleCore.Director = ALIFE_CoreObject("Director");
    //ExampleCore.Packet_Ninja = ALIFE_CoreObject("Packet Ninja");

    ExampleCore.director.Error("HEY YO!");
    CreateAppWindow(&ExampleCore);
    return 0;
}


