#include "Core.h"
#include "File_Wizard.h"


int main()
{

	Core::Initialise();

	//Core::File_Wizard::Set_Folder_Path("Settings Folder", dir_path("Config"));
	INFOe("Test Value returns {} from settings", Core::File_Wizard::Get_Setting("Test Section", "Test Value"));
	
	

	return 0;
}