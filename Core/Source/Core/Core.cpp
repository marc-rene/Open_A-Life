#include "Core.h"
#include "Log.h"
#include "File_Wizard.h"
#include <future>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;



namespace Core {

	void Initialise()
	{
		std::map<std::string, std::future<mint>> core_initialisation_futures;


		// --- STEP 1 : Initalise the Core and Engine Logger FIRST -----------------------------------
		// 

		if (Log::Init() != 0)
		{
			exit(1);	// Logger Init returned 1, great disaster
		}
		
		if (File_Wizard::Init() != 0)
		{
			exit(1);
		}


		// --- STEP 2 : Now we need to add to our futures,,, lets make this Async!!! -----------------
		//

		core_initialisation_futures["CSV TEST"] = std::async(std::launch::async, File_Wizard::test_csv_io);
		core_initialisation_futures["INI TEST"] = std::async(std::launch::async, File_Wizard::test_ini_io);





		// --- STEP 3 : Now... we wait for everything to finish --------------------------------------
		for (const auto& [key, future] : core_initialisation_futures)
		{
			switch (std::future_status status = future.wait_for(10s); status)
			{
			case std::future_status::deferred:
				WARNc("Future for {} is returned as deferred... wtf??? HOW?", key);
				break;
			case std::future_status::timeout:
				ERRORc("Future for {} has timed out... Great Disaster", key);
				break;
			case std::future_status::ready:
				INFOc("Future for {} completed ok! ", key);
				break;
			}
		}


		for (const auto& [key, future] : core_initialisation_futures)
		{
			if (core_initialisation_futures[key].get() != 0)
			{
				exit(1);
			}
		}
	}


};