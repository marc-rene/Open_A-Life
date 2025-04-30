#include "CreateWindow.h"
#include "Windows/All_Windows.h"
#include "Open_ALife.h"
#include <Mouse.h>
// Main code
int main(int, char**)
{
    A_LIFE::ALIFE_SCENARIO ExampleCore;
    ExampleCore.Init();



    CreateAppWindow(&ExampleCore);

    return 0;
}


