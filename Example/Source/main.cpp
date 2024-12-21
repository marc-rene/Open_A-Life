#include "CreateWindow.h"
#include "Windows/All_Windows.h"
#include "Core/Core.h"

// Main code
int main(int, char**)
{
    Core::OPEN_ALIFE_CORE ExampleCore;
    

    CreateAppWindow(&ExampleCore);
    
    return 0;
}


