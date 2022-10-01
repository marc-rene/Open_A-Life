#include "Declarations.h"
#include "File_IO.h"
#pragma once


void Get_Set_Global_Settings()
{
	Global_settings.HOW_MANY_FACTIONS 			= Get_Value_From_Settings("HOW MANY FACTIONS");
	Global_settings.LOG_LEVEL					= Get_Value_From_Settings("LOG LEVEL");
	Global_settings.WORLD_WIDTH					= Get_Value_From_Settings("WORLD WIDTH");
	Global_settings.WORLD_HEIGHT				= Get_Value_From_Settings("WORLD HEIGHT");
	Global_settings.File_ReOpen_Attempts		= Get_Value_From_Settings("File Reopen Attempts");
	Global_settings.USE_HIGH_PERFORMANCE_MODE	= Get_Value_From_Settings("...Gotta go fast?");
	Global_settings.SPEED_DIVIDER				= Get_Value_From_Settings("SPEED DIVIDER");
	
	Global_settings.WORLD_SIZE = Global_settings.WORLD_WIDTH * Global_settings.WORLD_HEIGHT;
}








