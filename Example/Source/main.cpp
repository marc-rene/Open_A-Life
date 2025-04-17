#include "CreateWindow.h"
#include "Windows/All_Windows.h"
#include "Open_ALife.h"

// Main code
int main(int, char**)
{
    A_LIFE::ALIFE_SCENARIO ExampleCore;
    ExampleCore.Init();
    CreateAppWindow(&ExampleCore);

    INFO("Director", "HELLO FROM ME TOO!");
    INFO("Fakerector", "HELLO FROM ME THREE !");
    
    return 0;
}


