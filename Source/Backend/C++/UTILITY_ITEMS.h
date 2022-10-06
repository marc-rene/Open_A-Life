#include "Declarations.h"
#include "File_IO.h"
#pragma once



void Get_Set_Global_Settings()
{
	LOG("Loading Values now from .alc", BORING, no_error, true);

	Global_settings.HOW_MANY_FACTIONS 			= Get_Value_From_Settings(	"HOW MANY FACTIONS"	);
	Global_settings.LOG_LEVEL					= Get_Value_From_Settings(	"LOG LEVEL"			);

	Global_settings.WORLD_WIDTH					= Get_Value_From_Settings(	"WORLD WIDTH"	);
	Global_settings.WORLD_HEIGHT				= Get_Value_From_Settings(	"WORLD HEIGHT"	);	

	Global_settings.File_ReOpen_Attempts		= Get_Value_From_Settings(	"File Reopen Attempts"	);
	Global_settings.USE_HIGH_PERFORMANCE_MODE	= Get_Value_From_Settings(	"...Gotta go fast?"		);
	Global_settings.SPEED_DIVIDER				= Get_Value_From_Settings(	"SPEED DIVIDER"			);
	

	// Now to check the wrap setting!
	int test 	=	Get_Value_From_Settings("World Wrap Setting?");
	if (test > 3 || test < 0)
	{
		LOG("The wrap setting in the .alc was wonky, setting it to no wrap", MINOR_ERROR);
		Global_settings.World_Wrap_Setting	=	No_Wrap;
	}
	else
	{
		Global_settings.World_Wrap_Setting	=	(World_Wrap_Config)test;
	}
	

	Global_settings.WORLD_SIZE 			= 	Global_settings.WORLD_WIDTH * Global_settings.WORLD_HEIGHT; 
}








