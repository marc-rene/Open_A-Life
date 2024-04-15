#include "Core.h"
#include "File_Wizard.h"


int main()
{

	Core::Initialise();

	Core::File_Wizard::List_Environment_Vars();

	return 0;
}