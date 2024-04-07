#include "Core.h"
#include "Log.h"
#include "File_Wizard.h"
#include <future>

#include <iostream>


namespace Core {

	void Initialise()
	{
		// Initalise the Core and Engine Logger
		bool log_success = Log::Init();
		if (log_success == false)
		{
			// Logger Init returned 1, great disaster
			exit(1);
		}

		// Test Our CSV abilities real quick async
		std::future<bool> csv_test_future = std::async(std::launch::async, File_Wizard::test_file_io);
		csv_test_future.wait();
		bool csv_success = csv_test_future.get();
		if (csv_success == false)
		{
			exit(1);
		};
	}


};