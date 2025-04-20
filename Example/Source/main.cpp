#include "CreateWindow.h"
#include "Windows/All_Windows.h"
#include "Open_ALife.h"

// Main code
int main(int, char**)
{
    A_LIFE::ALIFE_SCENARIO ExampleCore;
    ExampleCore.Init();

    auto test = A_LIFE::File_Wizard::List_Environment_Vars();
    INFOc(test);
    CreateAppWindow(&ExampleCore);

    return 0;
}


