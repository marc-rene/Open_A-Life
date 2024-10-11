/*
#include "Director.h"
#include "Core.h"
#include <mutex>
#include <future>
#include <chrono>
#include <cmath>
#include <fstream>
namespace Core
{

}






// Testing
namespace Core
{


	std::mutex thread_test_increment_mutex;

	bool simulate_thread_work(unsigned int* target_int)
	{
		//INFOc("Got value {} of address {}", *target_int, fmt::ptr(target_int));
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500));

		thread_test_increment_mutex.lock();
		try {
			*target_int = *target_int + 1;
		}
		catch (...)
		{
			thread_test_increment_mutex.unlock();
			return false;
		}
		thread_test_increment_mutex.unlock();

		return true;
	}


	mint Director::stress_test_thread_SERIAL(uMint test_size = 5)
	{
		unsigned int thread_test_int;
		srand(time(NULL));

		std::ofstream results_file;
		results_file.open("Thread Stress Test Result.txt", std::ios_base::app); // append instead of overwrite
		results_file << "\n------------------------------------------------------------------------\n";
		results_file << "\tSERIAL Thread Stress Test Results as of " << std::chrono::system_clock::now();
		results_file << "\n\n";
		try {
			for (uMint i = 0; i < test_size; i++)
			{
				INFOc("Starting SERIAL Stress Test {} / {}", (i + 1), test_size);
				TIMER_START;
				thread_test_int = 0;


				for (unsigned int x = 0; x < pow(2, i); x++)
				{
					if (simulate_thread_work(&thread_test_int) == false)
						return 1;
				}


				if (thread_test_int == pow(2, i))
				{
					SUCCESSc("Thread Test {} / {} passed BEAUTIFULLY in {:.4} seconds!", (i + 1), test_size, sw); // sw is from the TIMER_START macro
					results_file << "Thread Test (" << (i + 1) << " / " << static_cast<unsigned>(test_size) << ") passed BEAUTIFULLY in " << sw.elapsed() << std::endl;
				}
				else
				{
					ERRORc("Thread Stress Test {} / {} encountered an error... Threads incremented test int to {}, expecting {}", (i + 1), test_size, thread_test_int, pow(2, i));
					results_file << "\nThread Test (" << (i + 1) << " / " << static_cast<unsigned>(test_size) << ") encountered an error... Threads incremented test int to " << thread_test_int << " instead of " << pow(2, i) << "\n";
				}
			}

			results_file.close();
		}
		catch (const std::exception& ex)
		{
			WARNc("Serial Thread Stress Test failed {}", ex.what());
			return 99;
		}

		return 0;
	}


	mint Director::stress_test_threads(const bool use_async, const uMint test_size = 5)
	{

		if (test_size > 10)
			WARNc("Thread Test size of {} is VERY large, 2^{} = {} ", test_size, test_size, pow(2, test_size));

		const char* Thread_Type;

		if (use_async)
			Thread_Type = "ASYNC";
		else 
			Thread_Type = "DEFFERED";

		unsigned int thread_test_int;

		try
		{
			srand(time(NULL));

			WARNc("Trying to pre-allocate a vector of size {} bytes", (sizeof(std::vector<std::future<bool>>) * pow(2, test_size)));

			std::vector<std::future<bool>> test_futures(pow(2, test_size));

			std::ofstream results_file;
			results_file.open("Thread Stress Test Result.txt", std::ios_base::app); // append instead of overwrite
			results_file << "\n------------------------------------------------------------------------\n";
			results_file << "\t " << Thread_Type << " Thread Stress Test Results as of " << std::chrono::system_clock::now();
			
			results_file << "\n\n";


			for (uMint i = 0; i < test_size; i++)
			{
				const unsigned int current_thread_test_size = pow(2, i);
				INFOc("Starting {} Thread Stress Test {} / {}\t {} threads ", Thread_Type, (i + 1), test_size, current_thread_test_size);
				TIMER_START;
				thread_test_int = 0;


				if (test_futures.empty())
					WARNc("HEY! Thread Test Vector returns empty even after allocation... size is {}", test_futures.capacity());



				for (unsigned int x = 0; x < pow(2, i); x++)
				{
					//INFOc("Passing {} (address: {})", thread_test_int, fmt::ptr(&thread_test_int) );
					if (use_async)
						test_futures[x] = std::async(std::launch::async, simulate_thread_work, &thread_test_int);
					else
						test_futures[x] = std::async(std::launch::deferred, simulate_thread_work, &thread_test_int);
				}


				unsigned int index = 0;
				for (unsigned int x = 0; x < pow(2, i); x++)
				{
					std::future_status status = test_futures[x].wait_for(std::chrono::seconds(10));
					switch (status)
					{
					case std::future_status::deferred:
						// WARNc("Future for Thread {} is returned as deferred... Interesting?", index);
						break;
					case std::future_status::timeout:
						ERRORc("Future for Thread {} has timed out... Great Disaster", index);
						break;
					case std::future_status::ready:
						break;
					default:
						ERRORc("Future for Thread {} returned an unknown error... Great Disaster", index);
						break;
					}
					if (test_futures[x].get() == false)
						WARNc("Thread FAILED during stress test");

					index++;
				}

				if (thread_test_int == current_thread_test_size)
				{
					SUCCESSc("{} Thread Test {} / {} passed BEAUTIFULLY in {:.4} seconds!", Thread_Type, (i + 1), test_size, sw); // sw is from the TIMER_START macro
					results_file << Thread_Type << " Thread Test (" << (i + 1) << " / " << static_cast<unsigned>(test_size) << ") passed BEAUTIFULLY in " << sw.elapsed() << std::endl;
				}
				else
				{
					ERRORc("{} Thread Stress Test {} / {} encountered an error... Threads incremented test int to {}, expecting {}", Thread_Type, (i + 1), test_size, thread_test_int, current_thread_test_size);
					results_file << "\n" << Thread_Type << " Thread Test(" << (i + 1) << " / " << static_cast<unsigned>(test_size) << ") encountered an error... Threads incremented test int to " << thread_test_int << " instead of " << current_thread_test_size << "\n";
				}
			}

			results_file.close();
		}
		catch (const std::exception& ex)
		{
			WARNc("Thread Stress Test failed {}", ex.what());
			return 99;
		}


		return 0;
	}
}*/