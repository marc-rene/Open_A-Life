#include "Declarations.h"
#include "World.h" // for coordinate structs
#include "File_IO.h"
#pragma once



void Get_Set_Global_Settings()
{
	LOG("Loading Values now from .alc", BORING, no_error, true);

	Global_settings.HOW_MANY_FACTIONS_START 	= Get_Value_From_Settings(	"STARTING NUMBER OF FACTIONS"	);
	Global_settings.MAX_NUMBER_OF_FACTIONS 		= Get_Value_From_Settings(	"MAX NUMBER OF FACTIONS"	);
	Global_settings.HOW_MANY_FACTIONS_START 	= Get_Value_From_Settings(	"STARTING NUMBER OF AGENTS"	);
	Global_settings.MAX_NUMBER_OF_AGENTS 		= Get_Value_From_Settings(	"MAX NUMBER OF AGENTS"	);
	Global_settings.LOG_LEVEL			= Get_Value_From_Settings(	"LOG LEVEL"			);

	Global_settings.WORLD_WIDTH			= Get_Value_From_Settings(	"WORLD WIDTH"	);
	Global_settings.WORLD_HEIGHT			= Get_Value_From_Settings(	"WORLD HEIGHT"	);	

	Global_settings.File_ReOpen_Attempts		= Get_Value_From_Settings(	"File Reopen Attempts"	);
	Global_settings.USE_HIGH_PERFORMANCE_MODE	= Get_Value_From_Settings(	"...Gotta go fast?"		);
	Global_settings.SPEED_DIVIDER			= Get_Value_From_Settings(	"SPEED DIVIDER"			);
	

	// Now to check the wrap setting!
	int test = Get_Value_From_Settings("World Wrap Setting?");
	if (test > 3 || test < 0)
	{
		LOG("The wrap setting in the .alc was wonky, setting it to no wrap", MINOR_ERROR);
		Global_settings.World_Wrap_Setting = No_Wrap;
	}
	else
	{
		Global_settings.World_Wrap_Setting = (World_Wrap_Config)test;
	}
	

	Global_settings.WORLD_SIZE 	= Global_settings.WORLD_WIDTH * Global_settings.WORLD_HEIGHT; 
}


void print_world(uMint mode)
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




