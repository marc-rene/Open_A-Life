#include "File_Wizard.h"
#include "Core.h"
#include <exception>
#include <fstream>
#include <iostream>
#include "Log.h"
#include "csv.hpp"
#include "string"
#include "array"

namespace Core
{
	bool File_Wizard::test_file_io()
	{
		INFOc("Testing CSV file IO");

		try
		{
			TIMER_START;
			const char* test_file_name = "Test CSV Check.csv";
			std::ofstream test_file = std::ofstream(test_file_name);

			test_file << "\"c1\",\"c2\",\"c3\"\n\"c1d0\",\"c2d0\",\"c3d0\"\n\"c1d1\",\"c2d1\",\"c3d1\"\n\"c1d2\",\"c2d2\",\"c3d2\"";

			test_file.close();

			csv::CSVReader reader(test_file_name);

			std::array<std::string, 3> test_array;


			for (int index = 0; auto & row : reader) { // Input iterator

				test_array[index] = row["c2"].get<std::string>();
				index++;
			}

			if (test_array[0] == "c2d0")
			{
				SUCCESSc("CSV Test 1/3 passed");
			}
			else { throw std::runtime_error("CSV Parse Test Failed"); }

			if (test_array[1] == "c2d1")
			{
				SUCCESSc("CSV Test 2/3 passed");
			}
			else { throw std::runtime_error("CSV Parse Test Failed"); }

			if (test_array[2] == "c2d2")
			{
				SUCCESSc("CSV Test 3/3 passed");
			}
			else { throw std::runtime_error("CSV Parse Test Failed"); }


			std::remove(test_file_name);
			TIMER_ELAPSEDc("CSV Test passed in {:.4} seconds, GREAT SUCCESS");


		}

		catch (std::exception& ex)
		{
			ERRORc("ERROR : CSV Failed test {}", ex.what());

			return false;
		}



		return true;

	}

}