/*#include "File_Wizard.h"
#include "Core.h"
#include <exception>
#include <fstream>
#include <iostream>
#include "csv.hpp"
#include "string"
#include "array"
#include "ini.h"
#include <stdlib.h>
#include <map>
#include <mutex>


namespace Core
{
	static std::unordered_map<std::string, dir_path> OAL_Folders{
		{"Settings Folder", dir_path("Settings")},
		{"Data Folder", dir_path("Data")}
	};
	static bool			Init_Required = true;

	static dir_path*	Settings_Folder_Ref = &OAL_Folders["Settings Folder"];
	static dir_path*	Data_Folder_Ref = &OAL_Folders["Data Folder"];

	static std::string	Core_Settings_File_Name = "OAL Core Settings.ini";

	static std::mutex	Settings_File_Mutex;
	static std::mutex	OAL_Folders_Mutex;

	static mINI::INIFile settings_ini_file(file_path(*Settings_Folder_Ref / Core_Settings_File_Name).string());
	static mINI::INIStructure	settings_struct;

	void		File_Wizard::List_Environment_Vars()
	{
		mutex_lock folder_lock(OAL_Folders_Mutex);

		INFOc("Current Working Directory is {}", std::filesystem::current_path().string());

		for (auto& folder : OAL_Folders)
		{
			if (std::filesystem::is_directory(folder.second))
				INFOc("{} is : {}", folder.first, folder.second.string());

			else
				ERRORc("NO VALID FOLDER FOR {} IS SET!", folder.second.string());
		}
	}

	mint		File_Wizard::Init(bool create_folders_immidiatly)
	{
		if (Init_Required == false)
		{
			WARNc("File Wizard has already been initialised, Ignoring...");
			return 0;
		}
		try
		{
			mutex_lock OAL_Folder_lock(OAL_Folders_Mutex);
			mutex_lock Settings_lock(Settings_File_Mutex);

			for (auto& folder : OAL_Folders)
			{
				if (std::filesystem::is_directory(folder.second) && std::filesystem::exists(folder.second))
					INFOc("{} folder already exists", folder.first);
				else
					if (create_folders_immidiatly)
						std::filesystem::create_directory(folder.second);
			}

			// Do we have our Settings File ???
			file_path temp_settings_path = file_path(*Settings_Folder_Ref / Core_Settings_File_Name);
			if (std::filesystem::exists(temp_settings_path.string()) == false)	// Does't exist
			{
				WARNc("No {} File found in {} folder... Creating one now", Core_Settings_File_Name, Settings_Folder_Ref->string());
				std::ofstream OAL_Core_Settings = std::ofstream(temp_settings_path);

				OAL_Core_Settings << "------------------------------------------------------" << std::endl;
				OAL_Core_Settings << "Copyright : Coming soon...                            " << std::endl;
				OAL_Core_Settings << "------------------------------------------------------" << std::endl;
				OAL_Core_Settings << "                                                      " << std::endl;

				OAL_Core_Settings.close();
			}

			settings_ini_file = mINI::INIFile(temp_settings_path.string());
			settings_ini_file.read(settings_struct);


			//Now we check if we have data to work with
			if (std::filesystem::exists(*Data_Folder_Ref) == false)
			{
				WARNc("{} doesn't exist, creating it now");
				mkdir(Data_Folder_Ref->string().c_str());
			}

			Init_Required = false;
			return 0;
		}
		catch (const std::exception& ex)
		{
			ERRORc("ERROR WHEN INITIALISING FILE WIZARD : {}", ex.what());
			return 1;
		}
	}

	mint		File_Wizard::Set_Folder_Path(std::string folder_to_edit, dir_path new_path)
	{
		bool valid_key = false;

		std::lock_guard<std::mutex> lock(OAL_Folders_Mutex);

		// Did you enter the right Key??
		for (auto& key : OAL_Folders)
		{
			//TODO : LOWERCASE the strings first
			std::string folder_to_edit_lower = folder_to_edit;
			std::string key_lower = key.first;

			for (auto& c : folder_to_edit_lower)
				c = tolower(c);

			for (auto& c : key_lower)
				c = tolower(c);

			if (folder_to_edit_lower.compare(key_lower) == 0)
			{
				valid_key = true;
				key.second = new_path;
				INFOc("{} now set to {}", folder_to_edit, new_path.string());
				Init_Required = true;
				Init(true);
				return 0; // unlocks OAL Folder Mutex
			}
		}

		WARNc("HEY! {} ain't a valid key! Pain in my Asshole ", folder_to_edit);
		return 1;
	}

	std::string File_Wizard::Get_Setting(std::string Section, std::string Key)
	{
		settings_ini_file.read(settings_struct);

		INFOc("Value for {} is {} ", Key, settings_struct.get(Section).get(Key));

		if (settings_struct[Section].has(Key))
			return settings_struct[Section][Key];

		else
		{
			WARNc("{} is NOT in the {} section in Settings file", Key, Section);
			return "N/A";
		}
	}

	
	bool		File_Wizard::Set_Setting(std::string Section, std::string Key, std::string Value)
	{
		mutex_lock setting_lock(Settings_File_Mutex);

		settings_ini_file.read(settings_struct);
		settings_struct[Section][Key] = Value;
		
		return settings_ini_file.write(settings_struct);
	}

	std::vector<std::string>	File_Wizard::Get_CSV_Column_Data(file_path CSV_File, const char* Column_Name, const unsigned int allocation_size)
	{
		mint file_found_status = 0;
		file_path new_file_path = CSV_File;

		// Step 1 : Check and see if this file even exists??
		if (std::filesystem::exists(CSV_File))
			file_found_status = 1; // Safety


		for (auto& folder : OAL_Folders)
		{
			if (std::filesystem::exists(folder.second / CSV_File) && file_found_status <= 0) {
				file_found_status = 1;
				new_file_path = folder.second / CSV_File;
				WARNc("{} could only be found in the {} folder, assuming this is the right one ", CSV_File.string(), folder.first);
				break;
			}
		}


		if (file_found_status <= 0) // we failed
		{
			ERRORc("COULDN'T FIND CSV FILE {}", CSV_File.string());
			return std::vector<std::string>();
		}



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

	mint		File_Wizard::Transfer_File(file_path source_file, dir_path target_folder)
	{
		if (std::filesystem::exists(source_file))
		{
			WARNc("HEY! {} is not a valid file!", source_file.string());
			return 1;
		}

		return !std::filesystem::copy_file(source_file, target_folder); // copy file returns true == success, File_Wizard expects 0 == success
	}

	mint		File_Wizard::Transfer_Folder_Content(dir_path source_folder, dir_path target_folder)
	{
		// TODO : Fill this out with iterator
		return 1;
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

// Testing
namespace Core
{
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
}*/