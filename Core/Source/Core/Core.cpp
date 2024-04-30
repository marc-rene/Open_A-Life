#include "Core.h"
#include "Log.h"
#include "File_Wizard.h"
#include "Director.h"
#include <future>
#include <chrono>
#include <iostream>

#define THREAD_STRESS_TEST_SIZE 15

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
		
		INFOc("Open A-Life Core starting!");
		Print_CPU_Details();

		if (File_Wizard::Init(true) != 0)
		{
			exit(1);
		}


		// --- STEP 2 : Now we need to add to our futures,,, lets make this Async!!! -----------------
		//

		core_initialisation_futures["CSV TEST"] = std::async(std::launch::async, File_Wizard::test_csv_io);
		core_initialisation_futures["INI TEST"] = std::async(std::launch::async, File_Wizard::test_ini_io);
		//core_initialisation_futures["THREAD TEST SERIAL"] = std::async(std::launch::async, Director::stress_test_thread_SERIAL, 8);
		//core_initialisation_futures["THREAD TEST DEFFER"] = std::async(std::launch::async, Director::stress_test_threads, false, 8);
		core_initialisation_futures["THREAD TEST ASYNC"] = std::async(std::launch::async, Director::stress_test_threads, true, 8);




		// --- STEP 3 : Now... we wait for everything to finish --------------------------------------
		for (const auto& [key, future] : core_initialisation_futures)
		{
			std::future_status status = future.wait_for(10s);

			switch (status)
			{
			case std::future_status::deferred:
				WARNc("Future for {} is returned as deferred... wtf??? HOW?", key);
				break;

			case std::future_status::timeout:

				if (key.find("THREAD TEST") != std::string::npos)
					WARNc("Thread Stress Test is taking a while... OPTIMISATION NEEDED... ");

				else
					ERRORc("Future for {} has timed out... Great Disaster", key);
				break;

			case std::future_status::ready:
				INFOc("Future for {} completed ok! ", key);
				break;

			default:

				ERRORc("Future for {} returned an unknown error... Great Disaster!", key);
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


	// Thank you https://stackoverflow.com/a/850812
	void Print_CPU_Details()
	{
		int CPUInfo[4] = { -1 };
		unsigned   nExIds, i = 0;
		char CPUBrandString[0x40];

		// Get the information associated with each extended ID.
		__cpuid(CPUInfo, 0x80000000);
		nExIds = CPUInfo[0];

		for (i = 0x80000000; i <= nExIds; ++i)
		{
			__cpuid(CPUInfo, i);
			// Interpret CPU brand string
			if (i == 0x80000002)
				memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
			else if (i == 0x80000003)
				memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
			else if (i == 0x80000004)
				memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
		}

		INFOc("CPU Deatils are : {}", CPUBrandString);

		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);
		INFOc("Total RAM available : ~{}GB", status.ullTotalPhys / 1024000000 );

		return;
	}
};

