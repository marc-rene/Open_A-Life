/*#pragma once

#include "Core.h"  
#include "Type_Definitions.hpp"

namespace Core
{
	struct File_Wizard
	{
		static void			List_Environment_Vars();
		static mint			Init(bool = true);
		static mint			Set_Folder_Path(std::string, dir_path);
		static mint			Transfer_File(file_path, dir_path);
		static mint			Transfer_Folder_Content(dir_path, dir_path);
		
		static bool			Set_Setting(std::string, std::string, std::string);
		static std::string	Get_Setting(std::string, std::string);

		static std::vector<std::string> Get_CSV_Column_Data(file_path, const char*, const unsigned int);


		// OverLoads
		static std::vector<std::string> Get_CSV_Column_Data(const char*, const char*, const unsigned int);


		// Testing
		static mint test_csv_io();
		static mint test_ini_io();
	};
}
*/