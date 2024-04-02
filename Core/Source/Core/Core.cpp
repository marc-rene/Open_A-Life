#include "Core.h"
#include "Log.h"
#include "File_Wizard.h"

#include <iostream>


namespace Core {

	void Initialise()
	{
		 // Initalise the Core and Engine Logger
		if (Log::Init() == false)
		{
			// Logger Init returned 1, great disaster
			exit(1);
		}
	
		// Test Our CSV abilities real quick
		if (File_Wizard::test_file_io() == false)
		{
			exit(1);
		};
	}


};