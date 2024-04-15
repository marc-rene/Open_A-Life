#include "File_Wizard.h"
#include "Core.h"
#include <exception>
#include <fstream>
#include <iostream>
#include "Log.h"
#include "csv.hpp"
#include "string"
#include "array"
#include "ini.h"
#include <stdlib.h>

namespace Core
{
	void File_Wizard::List_Environment_Vars()
	{
		// TODO : Get Settings file path, Where all intermediate CSV files will be read from, etc...
	}

	mint File_Wizard::test_csv_io()
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
			return 1;
		}

		return 0;

	}


	mint File_Wizard::test_ini_io()
	{
		try
		{
			TIMER_START;
			const char* test_file_name = "Test INI check.ini";

			// create a file instance
			mINI::INIFile ini_file(test_file_name);

			// create a data structure
			mINI::INIStructure ini_structure;

			// populate the structure
			ini_structure["test"]["Value 1"] = "20";
			ini_structure["test"]["Value 2"] = "100";
			ini_structure["2nd Section"]["Value 3"] = "43";

			// generate an INI file (overwrites any previous file)
			ini_file.generate(ini_structure, true);

			std::string temp_read = ini_structure.get("test").get("VaLuE 1");

			// Test 1 - Getting values succeeds?
			if (ini_structure.get("test").has("Value 1") == true && temp_read.compare("20") == 0)
			{
				SUCCESSc("INI Test 1/3 passed");
			}
			else { throw std::runtime_error("INI Parse Test Failed"); }

			// Test 2 - Does the "has" method work?
			if (ini_structure.get("test").has("Value 3") == false && ini_structure.get("2nd sEcTiOn").has("Value 3") == true)
			{
				SUCCESSc("INI Test 2/3 passed");
			}
			else {

				throw std::runtime_error(std::format("value 3 of test section returned {} and value 3 of 2nd section returned {}", ini_structure.get("test").has("Value 3"), ini_structure.get("2nd sEcTiOn").has("Value 3")));
			}

			// Test 3 - Does INI update work?
			ini_structure["TeSt"]["vAlUe 2"] = "9999";
			if (ini_structure.get("test").get("Value 2").compare("9999") == 0)
			{
				SUCCESSc("INI Test 3/3 passed");
			}
			else { throw std::runtime_error("INI Parse Test Failed"); }

			TIMER_ELAPSEDc("INI Test passed in {:.4} seconds, GREAT SUCCESS");

			std::remove(test_file_name);
		}
		catch (const std::exception& ex)
		{
			ERRORc("ERROR : INI Failed test {}", ex.what());
			return 1;
		}

		return 0;
	}



}