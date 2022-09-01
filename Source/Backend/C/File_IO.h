#include "Declarations.h"
#pragma once



//	Check to make sure the file is successfully opened!
bool Check_file_is_open(FILE* file_to_check, char* file_name, const char* mode, int pause_duration, bool debugging)
{

	// Is sleep for the weak??? ',:/  //
	bool do_sleep = false;
	

	if (pause_duration != 0)
		{	do_sleep = true;		}


	//	Time to check! //
	if(file_to_check == NULL)
	{
		PRINT_MED_SEVERITY_ERROR;
		printf("\n%s Didn't open properly", file_name);
		printf("\nAttempting Re-open");

		// Lets try open the file a few more times
		for (mint i = 0; i < Global_settings.File_ReOpen_Attempts; i++)
		{

			if ( (file_to_check=fopen(file_name, mode)) != NULL)	// file opened successfully
			{
				if (debugging)
					{	BORING_LOG( ("%s successfully at last!", file_name) );	}
				
				return true;
			}

			else
			{
				printf(". ");
			}


			if(do_sleep)
				{	SLEEP(pause_duration);	}

		}//end for


		if (file_to_check == NULL)
		{

			PRINT_HIGH_SEVERITY_ERROR;
			CRUCIAL_LOG( ("THERE WAS AN ERROR OPENING %s", file_name) );
			
			return false;
		}//end if
		
	}//end if



	else if (file_to_check != NULL)
	{
		if (debugging)
			{	BORING_LOG( ("%s opened successfully first time round!", file_name) );	}

		return true;
	}//end elif
	

	PRINT_LOW_SEVERITY_ERROR;
	INTERESTING_LOG("...What? We reached the end of check if file is open function... we're not supposed to???")
	return false; // if nothing happened... then just WHAT???

}//end function





void Check_to_See_If_We_Should_Still_Be_Running(char* API_Folder_Path)
{
	char Status_file_path[FILE_PATH_BUFFER_SIZE];
	

	// First things first! We need to set up what the path even is! //
	for (uShort i = 0; i < FILE_PATH_BUFFER_SIZE; i++)
		{	Status_file_path[i] = '\0';	}	// make sure that every char is initialised and won't cause some damn runoff
	

	uShort x = 0;

	do
	{
		Status_file_path[x] = *(API_Folder_Path + x);
		x++;
	} 
	while ( *(API_Folder_Path + x) != '\0' );
	
	
	if (AM_I_RUNNING_WINDOWS) //windows?
		{	Status_file_path[x] = '\\';	}

	else //Linux?
		{	Status_file_path[x]	= '/';	}
	
	
	for (uShort i = 0; i < strlen(STATUS_READ_FILE); i++)
	{
		x++;
		Status_file_path[x] = STATUS_READ_FILE[i];
	}
	
	
	BORING_LOG( ("We're reading the status from: %s", Status_file_path) );
	BORING_LOG("Attempting to open now!");


	FILE* status_file;
	status_file = fopen(Status_file_path, "r");


	IF_HIGH_PERFORMANCE
	{
		if( Check_file_is_open(status_file, Status_file_path, "r", 1, false) )
			{	BORING_LOG( ("All's good opening %s", Status_file_path) );	}

		else
		{
			PRINT_HIGH_SEVERITY_ERROR;
			CRUCIAL_LOG( ("OH SHIT! %s wont open", Status_file_path) );
		}
	}

	IF_LOW_PERFORMANCE
	{ 
		if( Check_file_is_open(status_file, Status_file_path, "r", 5, false) )
			{	BORING_LOG( ("All's good opening %s", Status_file_path) );	}

		else
		{
			PRINT_HIGH_SEVERITY_ERROR;
			CRUCIAL_LOG( ("OH SHIT! %s wont open", Status_file_path) );
		}
		
	}
	


	char code; // will explain the different codes later!

	// Time to keep checking!
	do
	{
		status_file = fopen(Status_file_path, "r");

		if (Check_file_is_open(status_file, Status_file_path, "r", 1, false))
			{	code = fgetc(status_file);	}
		else
			{	CRUCIAL_LOG("Bad shit happened at Status check!");	}
		

		switch (code)
		{
			case '1':						//	Continue on
				printf("%c", code);
				break;
			
			case '0':						//	Exit
				printf("\nTime to stop");
				break;
			
			case EOF:
				printf("\nEND");
				break;
			
			default:						//	WTF?
				printf("\nError reading status, we getting %c", code);
				break;
		}//end switch


		fclose(status_file);
	
		SLEEP(1);

	} while (true);
	


}




