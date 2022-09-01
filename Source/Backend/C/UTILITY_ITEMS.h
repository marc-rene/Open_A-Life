#include "Faction_AI.h"



void Init_Global_Settings(char* API_Folder_Path)
{
	char API_Folder_Path_Copy[FILE_PATH_BUFFER_SIZE];
	strcpy(API_Folder_Path_Copy, API_Folder_Path);
	
	if (AM_I_RUNNING_WINDOWS)
		{ strcat(API_Folder_Path_Copy, '\\');	}
	else
		{ strcat(API_Folder_Path_Copy, '/');	}

	//These are just default settings
	Global_settings.HOW_MANY_FACTIONS 	=	10;
	Global_settings.LOG_LEVEL			=	3;
	Global_settings.WORLD_WIDTH			=	10;
	Global_settings.WORLD_HEIGHT		=	10;
	Global_settings.Random_Strength_Range_MAX	=	500;
	Global_settings.Random_Strength_Range_MIN	=	5;
	Global_settings.File_ReOpen_Attempts		=	20;
	Global_settings.USE_HIGH_PERFORMANCE_MODE	=	true;
	Global_settings.WORLD_SIZE = Global_settings.WORLD_WIDTH * Global_settings.WORLD_HEIGHT;
	Global_settings.World_Write_File_ptr = strcat(API_Folder_Path_Copy, WORLD_WRITE_FILE);
	Global_settings.SPEED_DIVIDER = 1;




}








