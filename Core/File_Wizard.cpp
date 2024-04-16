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
	static dir_path Settings_Folder_Path;
	static dir_path Data_Folder_Path;

	static bool Already_Initialised = false;


	void File_Wizard::List_Environment_Vars()
	{
		INFOc("Current Working Directory is {}", std::filesystem::current_path().string() );
		
		// Settings
		if (std::filesystem::is_directory(Settings_Folder_Path))
			INFOc("Settings Folder is : {}", Settings_Folder_Path.string() );
		else
			ERRORc("NO VALID FOLDER FOR SETTINGS IS SET!");
		
		// Data
		if (std::filesystem::is_directory(Data_Folder_Path))
			INFOc("Data Folder is : {}", Data_Folder_Path.string() );
		else
			ERRORc("NO VALID FOLDER FOR DATA IS SET!");

	}

	mint File_Wizard::Init()
	{
		if (Already_Initialised == true)
		{
			WARNc("File Wizard has already been initialised, Ignoring...");
			return 0;
		}
		try
		{
			Settings_Folder_Path = "Settings";
			Data_Folder_Path = "Data";

			// Settings
			if (std::filesystem::is_directory(Settings_Folder_Path) && std::filesystem::exists(Settings_Folder_Path) )
				INFOc("Settings folder already exists");
			else
				std::filesystem::create_directory(Settings_Folder_Path);
			
			// Data
			if (std::filesystem::is_directory(Data_Folder_Path) && std::filesystem::exists(Data_Folder_Path) )
				INFOc("Data folder already exists");
			else
				std::filesystem::create_directory(Data_Folder_Path);
			

			List_Environment_Vars();
			Already_Initialised = true;
			return 0;
		}
		catch (const std::exception& ex)
		{
			ERRORc("ERROR WHEN INITIALISING FILE WIZARD : {}", ex.what());
			return 1;
		}
	}

	

	std::vector<std::string> File_Wizard::Get_CSV_Column_Data(file_path CSV_File, const char* Column_Name, const unsigned int allocation_size)
	{
		mint file_found_status = 0;
		file_path new_file_path = CSV_File;

		// Step 1 : Check and see if this file even exists??
		do
		{
			if (std::filesystem::exists(CSV_File))
			{
				file_found_status = 99; // Safety
				break;
			}

			else if (std::filesystem::exists(Data_Folder_Path / CSV_File))
			{
				file_found_status = 99;
				new_file_path = Data_Folder_Path / CSV_File;
				WARNc("{} could only be found in the Data folder, assuming this is the right one ", CSV_File.string());
				break;
			}

			else if (std::filesystem::exists(Settings_Folder_Path / CSV_File))
			{
				file_found_status = 99;
				new_file_path = Settings_Folder_Path / CSV_File;
				WARNc("{} could only be found in the Settings folder, assuming this is the right one ", CSV_File.string());
				break;
			}

			else if (file_found_status == 2) // we failed
			{
				ERRORc("COULDN'T FIND CSV FILE {}", CSV_File.string());
				file_found_status = 99; // just incase return doesn't stop operation
				return std::vector<std::string>();
				
			}
			else
			{
				WARNc("COULDN'T FIND CSV FILE {}, going to try again but with .csv extention", CSV_File.string());
				file_found_status = 2;
				CSV_File += ".csv"; // try again
			}
		} while (file_found_status != 99);
		

		
		// Step 2 : Awesome lets get it
		INFOc("Trying to open CSV File : {}", new_file_path.string());
		csv::CSVReader reader(new_file_path.string());
		
		std::vector<std::string> entries_buffer;
		entries_buffer.reserve(allocation_size); 

		for (csv::CSVRow& row : reader) { // Input iterator
			entries_buffer.push_back(row[Column_Name].get<std::string>());
		}

		return entries_buffer;
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



// Overloads
namespace Core
{
	std::vector<std::string> File_Wizard::Get_CSV_Column_Data(const char* CSV_File, const char* Column_Name, const unsigned int allocation_size)
	{
		return Get_CSV_Column_Data(file_path(CSV_File), Column_Name, allocation_size);
	}
}