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
	

	// We should never get here!
	PRINT_LOW_SEVERITY_ERROR;
	INTERESTING_LOG("...What? We reached the end of check if file is open function... we're not supposed to???");

	return false; // if nothing happened... then just WHAT???

}//end function





void Check_to_See_If_We_Should_Still_Be_Running(char* API_Folder_Path)
{
	char Status_file_path[FILE_PATH_BUFFER_SIZE];
	

	strcpy(Status_file_path, API_Folder_Path); // We Now have the API folder path

	

	//	What OS are we on ???
	if (AM_I_RUNNING_WINDOWS) // Windows?
		{	strcat(Status_file_path, "\\");	}

	else // Windowsn't?
		{	strcat(Status_file_path, "/");	}
	
	
	strcat(Status_file_path, STATUS_READ_FILE); // Now we should have our whole file path!
	
	
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
	}//end if high performance

	IF_LOW_PERFORMANCE
	{ 
		if( Check_file_is_open(status_file, Status_file_path, "r", 5, false) )
			{	BORING_LOG( ("All's good opening %s", Status_file_path) );	}

		else
		{
			PRINT_HIGH_SEVERITY_ERROR;
			CRUCIAL_LOG( ("OH SHIT! %s wont open", Status_file_path) );
		}
	}//end if low performance
	


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


		fclose(status_file); // gotta close and let changes happen and be read
	
		IF_HIGH_PERFORMANCE
			{	SLEEP(1);	}

		IF_LOW_PERFORMANCE
			{	SLEEP(5);	}

	} while (true);
	
	// Don't think we should ever get here... but if we do it's better to be free 
	free(Status_file_path);

}



char* Get_Time()
{
	//	BE CAREFUL TO FREE THIS DUDE WHENEVER YOU GET THE CHANCE
	static char time_string[128];
	

	for (unsigned int i = 0; i < 128; i++)
	{
		time_string[i] = '\0';	//just to make sure
	}
	

	//	Thanks https://www.epochconverter.com/programming/c
	time_t epoch_time = time(NULL);
    struct tm  ts;

    // 	Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&epoch_time);

    strftime(time_string, sizeof(time_string), "%a %Y-%m-%d %H:%M:%S %Z", &ts);


	for (unsigned i = 0; i < 128; i++)
	{
		if (time_string[i] == '\0' )
		{
			time_string[i] = ' ';
			time_string[i+1] = ';';
			time_string[i+2] = ' ';
			break;
		}
	}

	return time_string;
}


bool Log_To_File(char* message)
{
	unsigned int message_length = 0;
	
	while (message[message_length] != '\0')
	{
		message_length++;
	}


	//	Write the Time part	
	char* time_part = Get_Time();

	for (unsigned __int8 i = 0; i < 128; i++)
	{
		fputc(time_part[i], Global_settings.Log_File_Ptr);
	}

	free(time_part);
	


	for (unsigned int i = 0; i < message_length; i++)
	{
		fputc(message[i], Global_settings.Log_File_Ptr);
	}


	fputc('\n', Global_settings.Log_File_Ptr);


}



void Get_Value_From_Settings()
{
	// make sure it's found first
	while (true)
	{
		SLEEP(2);
		printf(".");
	}
	
}