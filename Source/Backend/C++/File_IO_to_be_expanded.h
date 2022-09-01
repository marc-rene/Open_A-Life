#include 				"Declarations.h"




bool Check_File_Is_Open(std::ifstream*, bool);
bool Attempt_File_Reopening(std::ifstream*, uShort, uShort, bool);




bool Check_File_Is_Open(std::ifstream* file_ptr, bool is_essential = false)
{
	if ( !(file_ptr->is_open() ) ) 	// file pointer is invalid 
	{
		IF_HIGH_PERFORMANCE
		{	return Attempt_File_Reopening(file_ptr, 10, 10);	}

		IF_LOW_PERFORMANCE
		{	return Attempt_File_Reopening(file_ptr, 10, 250);	}
	}

	else if( file_ptr->is_open() ) // it's valid and open! 
	{
		return true;
	}

	else
	{
		HIGH_LOG("Error Checking if a file was open");
		return false;
	}
}


bool Attempt_File_Reopening(std::ifstream* file_ptr, uShort how_many_tries, uShort wait_time = 0, bool is_esstential = false)
{
	for (uShort i = 0; i < how_many_tries; i++)
	{
		*file_ptr.
	}
	
}



bool Copy_File_Contents(const char* source_file_address, const char* destination_file_address)
{
	//	https://stackoverflow.com/a/10195497
	//	May you have wonderful dreams and prosper in life: 
	//	Merci beaucoup et faire des bon rêves chaque jour mon pote!
	//  谢谢我的朋友！您太棒了! 对不起我不知道汉语... 我是学生中文 :) 
	
	std::ifstream  src(source_file_address, 		std::ios::binary);
	std::ofstream  dst(destination_file_address,   	std::ios::binary);
	
	if (!src)
	{
		MED_LOG(MED_SEVERITY_ERROR);
		MED_LOG("\nError in Copying file function. Source file has some issues");
		return false;
	}
	
	if (!dst)
	{
		MED_LOG(MED_SEVERITY_ERROR);
		MED_LOG("\nError in Copying file function. Destination file has some issues");
		return false;
	}
	
	dst << src.rdbuf();
	src.close();
	dst.close();

	return true;
}



bool Copy_File_Contents(std::ifstream* source_file_ptr, std::ofstream* destination_file_ptr)
{
	if (!(*source_file_ptr))
	{
		MED_LOG(MED_SEVERITY_ERROR);
		MED_LOG("\nError in Copying file function. Source file has some issues");
		return false;
	}
	
	if (!(*destination_file_ptr))
	{
		MED_LOG(MED_SEVERITY_ERROR);
		MED_LOG("\nError in Copying file function. Destination file has some issues");
		return false;
	}
	
	*destination_file_ptr << source_file_ptr->rdbuf();

	return true;
}




////////////////////////			Should we Exit or not?			////////////////////	

void Check_to_See_If_We_Should_Still_Be_Running()
{
	/*	The way this should work is by opening the Keep_Reading.bool file
		and exit if a 1 is read, or ignore if nothing is read				*/
	bool Stay_Alive = 	true;
	bool First_Run	=	true;

	do
	{
		std::fstream	file(STATUS_READ_FILE_PATH);
		
		if (!file)	// Was the file opened successfully?
		{
			for (uMint i = 0; i < 10; i++)
			{
				if (file)
				{
					break; // yay! it worked 
				}

				else
				{
					printf(LOW_SEVERITY_ERROR);
					printf("\nAh fiddlestciks! We couldn't open the status file to determine if we should keep going or not\ntrying to open file again!\nWish us luck");
					file.open(STATUS_READ_FILE_PATH);
					SLEEP(SPEED_DIVIDER);
				}//end else
				
				SLEEP( SPEED_DIVIDER*5 );	
			}//end child if

			if (!file) 	// is it still not working??? 
			{
				printf(HIGH_SEVERITY_ERROR);
				printf("\nWE CANT DETERMINE IF WE WILL CONTINUE ON OR NOT!!! \nPRAY HARDER NEXT TIME");
				printf("\n\nCHECK TO SEE IF Keep_Reading.bool IS IN THE CURTAINS FOLDER!\n");
				exit(-1);
			}//end child if

		}//end parent if
		
		std::string temp_string;

		std::getline(file,	temp_string);	// read the file and copy the output into temp_string


		if ( temp_string.find("Continue") != std::string::npos )
		{
			//We keep swimming
			SLEEP(SPEED_DIVIDER*10);
		}

		else if ( temp_string.find("Exit") != std::string::npos )
		{
			//Nevermind, lets close!
			Stay_Alive	=	false;
			Exiting = true;
			printf("\n\n\t\tATTENTION!\tWE GONNA SELF-DESTRUCT NOW!\n\t\t\tEXITING");
			SLEEP(SPEED_DIVIDER);
			printf(".");
			SLEEP(SPEED_DIVIDER);
			printf(".");
			SLEEP(SPEED_DIVIDER);
			printf(".");
			SLEEP(SPEED_DIVIDER);
			printf("\n\nBye bye :)");
			SLEEP(SPEED_DIVIDER);
		}

		else
		{
			HIGH_LOG(MED_SEVERITY_ERROR << "\nWe couldn't make sense of the Keep_Reading file so we just gonna assume that it's a 'continue' there");

			file.close();
			SLEEP(SPEED_DIVIDER);

			std::ofstream out_file(STATUS_READ_FILE_PATH);
			out_file << "Continue";
			out_file.close();
		}
		
		if(First_Run)
		{
			Permission_to_work = true;
			First_Run = false;
		}

		file.close();
		SLEEP( SPEED_DIVIDER*10 );

	} while (Stay_Alive);
}//end function




	