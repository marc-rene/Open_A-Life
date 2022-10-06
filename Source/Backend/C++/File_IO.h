#include "Declarations.h"
#pragma once



// This is the MAIN LOG function
void LOG(const char* message, Importance min_log_level, Error_Types severity, bool log_to_file_too)
{
	if(Global_settings.LOG_LEVEL >= min_log_level)
	{	
		printf("\n"); 
		printf(message);

		if (log_to_file_too)
		{
			switch (severity)
			{
				case SEVERE_ERROR:
					Log_To_File(HIGH_SEVERITY_ERROR);
					break;
				case MILD_ERROR:
					Log_To_File(MED_SEVERITY_ERROR);
					break;
				case MINOR_ERROR:
					Log_To_File(LOW_SEVERITY_ERROR);
					break;
				
				default:
					break;
			}//end error switch

			Log_To_File(message);

		}//end if
	}//end root if
}

// Now for our different logging flavours
void LOG(std::string message, Importance min_log_level, Error_Types severity, bool log_to_file_too)
{
	LOG(message.c_str(), min_log_level, severity, log_to_file_too);
}

void LOG(const char* message, Importance min_log_level)
{
	LOG(message, min_log_level, no_error, false);
}

void LOG(std::string message, Importance min_log_level)
{
	LOG(message.c_str(), min_log_level, no_error, false);
}

void LOG(const char* message)
{
	LOG(message, no_importance, no_error, false);
}

void LOG(std::string message)
{
	LOG(message.c_str(), no_importance, no_error, false);
}

void LOG(const char* message, Error_Types error_severity)
{
	LOG(message, IMPORTANT, error_severity, true);
}

void LOG(std::string message, Error_Types error_severity)
{
	LOG(message.c_str(), IMPORTANT, error_severity, true);
}



// Our default settings
Parametres Default_Parametres()
{
	Parametres temp_options;

	temp_options.HOW_MANY_FACTIONS_START	= 	10;
	temp_options.HOW_MANY_AGENTS_START		= 	10;
	temp_options.MAX_NUMBER_OF_FACTIONS		= 	20;
	temp_options.MAX_NUMBER_OF_AGENTS		= 	20;
	temp_options.LOG_LEVEL					= 	3;
	temp_options.WORLD_WIDTH				= 	10;
	temp_options.WORLD_HEIGHT				= 	10;
	temp_options.World_Wrap_Setting			=	Any_Wrap;
	temp_options.File_ReOpen_Attempts		= 	5;
	temp_options.USE_HIGH_PERFORMANCE_MODE 	= 	true;
	temp_options.WORLD_SIZE					= 	temp_options.WORLD_WIDTH * temp_options.WORLD_HEIGHT;
	temp_options.Log_File_Ptr				= 	fopen(LOG_FILE, "a");
	temp_options.API_Folder_Path 			= 	DEFAULT_API_FOLDER_PATH;
	temp_options.SPEED_DIVIDER				= 	1;

	return temp_options;
}



//	Check to make sure the file is successfully opened!
bool Check_File_Is_Open(FILE* file_to_check, const char* file_name, const char* mode, int pause_duration, bool debugging)
{

	// Is sleep for the weak??? ',:/  //
	bool do_sleep = false;
	

	if (pause_duration != 0)
		{	do_sleep = true;		}


	//	Time to check! //
	if(file_to_check == NULL)
	{
		LOG( ("%s Didn't open properly first time", file_name), MINOR_ERROR );
		printf("\nAttempting Re-open");

		// Lets try open the file a few more times
		for (mint i = 0; i < Global_settings.File_ReOpen_Attempts; i++)
		{

			if ( (file_to_check=fopen(file_name, mode)) != NULL)	// file opened successfully
			{
				if (debugging)
					{	LOG( ("%s opened successfully at last!", file_name) );	}
				
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
			LOG( ("THERE WAS AN ERROR OPENING %s", file_name), SEVERE_ERROR );
			
			return false;
		}//end if
		
	}//end if



	else if (file_to_check != NULL)
	{
		if (debugging)
			{	LOG( ("%s opened successfully first time round!", file_name) );	}

		return true;
	}//end elif
	

	// We should never get here!
	LOG("...What? We reached the end of check if file is open function... we're not supposed to???", MILD_ERROR);

	return false; // if nothing happened... then just WHAT???

}//end function



bool Check_File_Exists(const char* file_name, bool create_if_doesnt_exist)
{
	FILE* file_to_check = fopen(file_name, "r");


	for (uMint i = 0; i < Global_settings.File_ReOpen_Attempts; i++)
	{

		if (file_to_check == NULL)
		{
			if (Check_File_Is_Open(file_to_check, file_name, "r", 1, false) )
			{
				return true;
			}

			else
			{
				if (create_if_doesnt_exist)
				{
					file_to_check = fopen(file_name, "a");
				}
				else
				{
					return false;
				}
			}
		}

		//yay file exists
		else
		{
			return true;
		}
	}//end for

	//this should never be reached
	return false;
}



// This is here becuase code repetition occured
void Get_File_Path(const char* API_Folder_Path, const char* file_to_get, char* string_to_edit)
{
	// Clear up the string first
	for (unsigned i = 0; i < FILE_PATH_BUFFER_SIZE; i++)
	{
		string_to_edit[i] = '\0';
	}

	strcpy(string_to_edit, API_Folder_Path); 	 // We Now have the API folder path

	
	//	What OS are we on ???
	if (AM_I_RUNNING_WINDOWS) // Windows?
		{	strcat(string_to_edit, "\\");	}

	else // Windowsn't?
		{	strcat(string_to_edit, "/");	}

	
	strcat(string_to_edit, file_to_get); // Now we should have our whole file path!
	
	//Should have the path now!
}



// Check to see what we should do!
void Check_Status_File()
{
	char Status_file_path[FILE_PATH_BUFFER_SIZE];
	

	Get_File_Path(Global_settings.API_Folder_Path, STATUS_READ_FILE, Status_file_path);


	
	LOG( ("We're reading the status from: %s", Status_file_path), BORING, no_error, true );
	LOG("Attempting to open now!");


	FILE* status_file;
	status_file = fopen(Status_file_path, "r");


	IF_HIGH_PERFORMANCE
	{
		if( Check_File_Is_Open(status_file, Status_file_path, "r", 1, false) )
			{	LOG( ("All's good opening %s", Status_file_path) );	}

		else
		{
			LOG( ("OH POOP! %s wont open", Status_file_path), SEVERE_ERROR );
		}
	}//end if high performance

	IF_LOW_PERFORMANCE
	{ 
		if( Check_File_Is_Open(status_file, Status_file_path, "r", 5, false) )
			{	LOG( ("All's good opening %s", Status_file_path) );	}

		else
		{
			LOG( ("OH SHIT! %s wont open", Status_file_path), SEVERE_ERROR );
		}
	}//end if low performance
	


	char code = '\0'; // will explain the different codes later!

	// Time to keep checking!
	do
	{
		status_file = fopen(Status_file_path, "r");

		if (Check_File_Is_Open(status_file, Status_file_path, "r", 1, false))
			{	code = fgetc(status_file);	}
		else
			{	LOG("Bad stuff happened at Status check!", MILD_ERROR);	}
		

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



//	Verified works
void Log_To_File(const char* message, bool include_time)
{
	if (include_time)
	{
		//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-
		//	Ok this is just confusing! I stripped out unnessesary #includes
		// and I commented out time.h
		// This compiles flawlessly with time.h absent.... HOW??? 
		// What are you doing g++?
		// https://www.highlandernews.org/wp-content/uploads/2016/02/ops.meme_.nba_-1024x768.jpg
		//	...好了
		//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-
		
		//	Write the Time part	!
		const uShort time_buffer = 32;
		char time_part[time_buffer];


		// make sure all is null
		for (uShort i = 0; i < time_buffer; i++)
		{
			time_part[i] = '\0'; 
		}
		

		//	Thanks https://www.epochconverter.com/programming/c
		time_t epoch_time = time(NULL);
		struct tm  ts;

		// 	Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
		ts = *localtime(&epoch_time);

		strftime(time_part, sizeof(time_part), "%Y-%m-%d   %H:%M:%S", &ts);

		// add a little ; at the end
		for (unsigned i = 0; i < time_buffer; i++)
		{
			if (time_part[i] == '\0' )
			{
				time_part[i] = ' ';
				time_part[i+1] = ':';
				time_part[i+2] = ' ';
				break;
			}
		}
		
		
		for (unsigned __int8 i = 0; i < time_buffer; i++)
		{
			fputc(time_part[i], Global_settings.Log_File_Ptr);
		}
	}//end if to include time or nah

	else
	{
		fputc('\t', Global_settings.Log_File_Ptr);
		fputc('\t', Global_settings.Log_File_Ptr);
	}

	// Main message
	for (unsigned int i = 0; i < strlen(message); i++)
	{
		fputc(message[i], Global_settings.Log_File_Ptr);
	}


	fputc('\n', Global_settings.Log_File_Ptr);
}


//	verified works
void Log_To_File(const char* message)
{
	Log_To_File(message, true);
}


//	Verified works
void Log_To_File(std::string message)
{
	const char* charred_message = message.c_str();

	Log_To_File(charred_message, true);
}



//	Verified Works, not happy with invalid value detection
int Get_Value_From_Settings(const char* setting_to_search_for)
{
	char OAL_config_path[FILE_PATH_BUFFER_SIZE];

	Get_File_Path(Global_settings.API_Folder_Path, CONFIG_FILE, OAL_config_path);


	// make sure it's found first
	if ( Check_File_Exists(OAL_config_path, false) == false)
	{
		LOG("WE CANT FIND THE OAL CONFIG FILE", SEVERE_ERROR);
	}

	std::ifstream config_file(OAL_config_path);
	
	if (config_file.is_open() )
	{
		LOG("Successfully found and opened the config", no_importance, no_error, false);
	}
	else
	{
		LOG("ERROR OPENING CONFIG FILE", SEVERE_ERROR);
		exit(1); 	// exit
	}

	//	-	-	-	-	-	-	-	-	-
	//		Now lets get that value!


	std::string temp_string;
	while (std::getline(config_file, temp_string) ) 	// Go throught the file line by line
	{
		// Check our string if we found it!!!
		if(temp_string.find(setting_to_search_for) != std::string::npos)
		{
			uShort equal_index = 0;
			uShort end_index = 0;

			for(uShort i = 0; i < temp_string.length(); i++)
			{
				if (temp_string[i] == '=')
				{
					equal_index = i;
				}
				else if (temp_string[i] == ';')
				{
					end_index = i;
					break;
					LOG("Found setting", no_importance, no_error, true);
				}
			}

			if (equal_index == 0 || end_index == 0)
			{
				LOG("Ah poop, the settings file isn't correct, make sure every setting ends with a ; and has an = ", MILD_IMPORTANCE, MILD_ERROR, true);
			}
			


			// Our value lies betweem = and ;
			std::string extraction_string = temp_string.substr( (equal_index+1), (end_index-equal_index) );  
			std::string setting_stringed(setting_to_search_for); // std::string version of our setting
			
			chunky value = 0;
			
			try
			{
				value = std::stoi(extraction_string);
				
				std::string success_msg = setting_stringed + "\t:\t" + std::to_string(value);
				LOG(success_msg, BORING, no_error, true);
			}
			catch(...) //if any error comes up
			{
				std::string error_message = "HEY! HUGE Error getting value for " + setting_stringed + "... STD::STOI doesn't like it! I'ma give it a 0";
				LOG(error_message, MILD_ERROR);

				value = 0;
			}

			return value;
		}
	}
	
	// We shouldn't ever reach here
	LOG("ERROR GETTING VALUE FROM SETTINGS", MILD_IMPORTANCE, MILD_ERROR, true);
	printf("\n%s Threw an error in value retrival", setting_to_search_for);
	return 0;
}

