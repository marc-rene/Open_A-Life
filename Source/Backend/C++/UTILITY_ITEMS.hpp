#include 	"Declarations.hpp"
#include 	"World.h" // for coordinate structs

#pragma once


bool Open_Config()
{
	// Lets get the config file first!
	char OAL_config_path[FILE_PATH_BUFFER_SIZE];
	Get_File_Path(Global_settings.API_Folder_Path, CONFIG_FILE, OAL_config_path);


	// make sure it's found first
	if ( Check_File_Exists(OAL_config_path, false) == false)
		{	LOG("WE CANT FIND THE OAL CONFIG FILE", SEVERE_ERROR);	}


	Global_settings.Config_File.open(OAL_config_path);


	if (Global_settings.Config_File.is_open() )
	{	
		LOG("Successfully found and opened the config", no_importance);
		Global_settings.Config_file_is_open = true;
		
		return true;	
	}
	else
	{
		LOG("ERROR OPENING CONFIG FILE... BE CAREFUL", SEVERE_ERROR);
		Global_settings.Config_file_is_open = false;
	
		// Unsafe to use Check_File_Is_Open Cause can't determine if its the right time to use it or not
		return false;
	}


}



void Close_Config()
{
	LOG("Closing the config", no_importance);

	Global_settings.Config_File.close();

	Global_settings.Config_file_is_open = false;
}



void Get_Set_Global_Settings()
{
	LOG("Loading Values now from .alc", BORING, no_error, true);

	if(Open_Config() )
	{
		Global_settings.HOW_MANY_FACTIONS_START 	= Get_Value_From_Settings("STARTING NUMBER OF FACTIONS"	);
		Global_settings.MAX_NUMBER_OF_FACTIONS 		= Get_Value_From_Settings("ABS MAX NUMBER OF FACTIONS"	);
		Global_settings.HOW_MANY_FACTIONS_START 	= Get_Value_From_Settings("STARTING NUMBER OF AGENTS"	);
		Global_settings.MAX_NUMBER_OF_AGENTS 		= Get_Value_From_Settings("MAX NUMBER OF ACTVIVE AGENTS");
		Global_settings.LOG_LEVEL			= Get_Value_From_Settings("MINIMUM RUNTIME LOG LEVEL"	);

		Global_settings.WORLD_WIDTH			= Get_Value_From_Settings("WIDTH OF THE BACKEND WORLD"	);
		Global_settings.WORLD_HEIGHT			= Get_Value_From_Settings("HEIGHT OF THE BACKEND WORLD"	);

		Global_settings.File_ReOpen_Attempts		= Get_Value_From_Settings("ATTEMPT FILE REOPEN X TIMES"	);
		Global_settings.USE_HIGH_PERFORMANCE_MODE	= Get_Value_From_Settings("...Gotta go fast? extra text");
		Global_settings.SPEED_DIVIDER			= Get_Value_From_Settings("THE SPEED DIVIDER SETTING"	);
		Global_settings.Unix_Time_Read_Leeway		= Get_Value_From_Settings("Unix Time Difference Leeway" );
		

		// Now to check the wrap setting!
		int test = Get_Value_From_Settings("WHICH MODE FOR WORLD WRAP");
		if (test > 3 || test < 0)
		{
			LOG("The wrap setting in the .alc was wonky, setting it to no wrap", MINOR_ERROR);
			Global_settings.World_Wrap_Setting = No_Wrap;
		}
		else
		{
			Global_settings.World_Wrap_Setting = (World_Wrap_Config)test;
		}
		
		Close_Config();
		
		Global_settings.WORLD_SIZE 	= Global_settings.WORLD_WIDTH * Global_settings.WORLD_HEIGHT; 
	}

	else
	{
		LOG("ERROR GETTING CONFIG FILE", MILD_ERROR);
	}
}



void test_print_world(uMint mode)
{
	printf("\n\n");
	for (uInt i = 0; i < Global_settings.WORLD_SIZE; i++)
	{
		switch (mode)
		{
			case 0:
				printf("%lu\t", i);
				break;
			
			case 1:
				printf("%lu,%lu\t", Int_To_Co_Ordinates(i).X, Int_To_Co_Ordinates(i).Y);
				break;

			default:
				printf("?");
				break;
		}

		if(i % Global_settings.WORLD_WIDTH == Global_settings.WORLD_WIDTH - 1)
			{	printf("\n");	}
	}
	
}



void test_co_ords_index_conversions(uInt test)
{
	Co_Ordinates test_CO = Int_To_Co_Ordinates(test);
	uInt test_index = Co_Ordinates_to_Int(test_CO);
	
	printf	("\n%lu\treturns\t%lu:%lu\twhich returns back\t%lu",
			test,
			test_CO.X,test_CO.Y,
			test_index
		);
}




