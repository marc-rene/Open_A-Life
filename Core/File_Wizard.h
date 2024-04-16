#pragma once

#include "Core.h"  
#include "string"

#include "Type_Definitions.hpp"

namespace Core
{
	class File_Wizard
	{
	public:
		static void List_Environment_Vars();
		static mint Init();
		static mint test_csv_io();
		static mint test_ini_io();

		
		static std::vector<std::string> Get_CSV_Column_Data(file_path, const char*, const unsigned int);
		
		// OverLoads
		static std::vector<std::string> Get_CSV_Column_Data(const char*, const char*, const unsigned int);
		
	};
}
