#include "CreateWindow.h"
#include "Core.h"

// Main code
int main(int, char**)
{
    Core::OPEN_ALIFE_CORE ExampleCore;
    ExampleCore.UID = 2;

    CreateAppWindow(&ExampleCore);
    
    return 0;
}


