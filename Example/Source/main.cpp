#include "CreateWindow.h"
#include "Windows/All_Windows.h"
#include "Open_ALife.h"

// Main code
int main(int, char**)
{
    A_LIFE::ALIFE_SCENARIO ExampleCore;
    A_LIFE::Level testlevel("DEBUG LEVEL");
    ExampleCore.Init();


    CreateAppWindow(&ExampleCore);

    return 0;
}
