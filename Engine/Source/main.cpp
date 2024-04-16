#include "Core.h"
#include "File_Wizard.h"


int main()
{

	Core::Initialise();

	Core::File_Wizard::List_Environment_Vars();

	std::vector<std::string> names = Core::File_Wizard::Get_CSV_Column_Data(file_path("Last Names"), "EAST", 512);
	INFOe("Names is {} elements large", names.size());
	
	std::vector<std::string> names2 = Core::File_Wizard::Get_CSV_Column_Data(file_path("Last asdf"), "EAST", 512);
	INFOe("Names is {} elements large", names2.size());
	

	return 0;
}