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
		static mint test_csv_io();
		static mint test_ini_io();

	private:
		static const std::string Settings_Folder_Path;
	};
}
