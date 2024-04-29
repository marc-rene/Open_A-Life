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

	mint Director::stress_test_threads(uMint test_size = 5)
	{

		std::mutex thread_test_increment_mutex;

		if (test_size > 10)
			WARNc("Thread Test size of {} is VERY large, 2^{} = {} ", test_size, test_size, pow(2, test_size));

		unsigned int thread_test_int;

		auto simulate_thread = [&]()
			{

				std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500));

				thread_test_increment_mutex.lock();
				try {
					thread_test_int++;
				}
				catch (...)
				{
					thread_test_increment_mutex.unlock();
					return false;
				}
				thread_test_increment_mutex.unlock();

				return true;
			};

		try
		{
			srand(time(NULL));

			WARNc("Trying to pre-allocate a vector of size {} bytes", (sizeof(std::vector<std::future<bool>>) * pow(2, test_size)) );
			std::vector<std::future<bool>> test_futures(pow(2, test_size));

			std::ofstream results_file;
			results_file.open("Thread Stress Test Result.txt", std::ios_base::app); // append instead of overwrite
			results_file << "\n------------------------------------------------------------------------\n";
			results_file << "\tThread Stress Test Results as of " << std::chrono::system_clock::now();
			results_file << "\n\n";


			for (uMint i = 0; i < test_size; i++)
			{
				const unsigned int current_thread_test_size = pow(2, i);
				INFOc("Starting Thread Stress Test {} / {}\t {} threads ", (i + 1), (test_size + 1), current_thread_test_size);
				TIMER_START;
				thread_test_int = 0;


				if (test_futures.empty())
					WARNc("HEY! Thread Test Vector returns empty even after allocation... size is {}", test_futures.capacity());

				

				for (unsigned int x = 0; x < pow(2, i); x++)
				{
					test_futures[x] = std::async(std::launch::async, simulate_thread);
				}
			

				unsigned int index = 0;
				for (unsigned int x = 0; x < pow(2, i); x++)
				{
					std::future_status status = test_futures[x].wait_for(std::chrono::seconds(10));
					switch (status)
					{
					case std::future_status::deferred:
						WARNc("Future for Thread {} is returned as deferred... Interesting?", index);
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
					index++;
				}

				if (thread_test_int == current_thread_test_size)
				{
					SUCCESSc("Thread Test {} / {} passed BEAUTIFULLY in {:.4} seconds!", (i + 1), test_size, sw); // sw is from the TIMER_START macro
					results_file << "\nThread Test (" << (i + 1) << " / " << static_cast<unsigned>(test_size) << ") passed BEAUTIFULLY in " << (sw.elapsed_ms() / 1000) << " seconds!\n";
				}
				else
				{
					ERRORc("Thread Stress Test {} / {} encountered an error... Threads incremented test int to {}, expecting {}", (i + 1), test_size, thread_test_int, current_thread_test_size);
					results_file << "\nThread Test (" << (i + 1) << " / " << static_cast<unsigned>(test_size) << ") encountered an error... Threads incremented test int to " << thread_test_int << " instead of " << current_thread_test_size << "\n";
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
}