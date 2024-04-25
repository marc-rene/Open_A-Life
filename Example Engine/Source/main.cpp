#include "Core.h"
#include "File_Wizard.h"


int main()
{

	Core::Initialise();

	Core::File_Wizard::Set_Folder_Path("Settings Folder", dir_path("Config"));

	
	

	return 0;
}