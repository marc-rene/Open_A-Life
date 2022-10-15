#include 	"File_IO.hpp"
#include 	"UTILITY_ITEMS.hpp"
#include 	"World.h"
#include 	"logo.h"
#include 	"Faction_Definition.hpp"



//			It probably would have made more sense to write everything into the one file 
//		but oh lord, that would be hell to develop in!
//		I also understand that having mulitple #includes in the one cpp file might've made sense
//		but in this context this works perfectly fine! :)
//		
//
//			The purpose of this project is to make an open source version of the
//		A-Life system in the S.T.A.L.K.E.R video game francise that can be implemented into any 
//		application that may benefit from it, such as video games and/or visualisers.
//
//
//			The world is comprised into a 2d grid with different factions, Humans, Wildlife, etc...
//		can fight for territory, simply just exist in the world, and/or interact with it in numberous different ways.  
// 
//
//		The code is seperated into 3 clear-cut sections, and named using a restaurant as a metaphor:
//			1. 	The backend (what you are seeing here, is the kitchen)
//			2.	the API (the waitors)
//			3.	the frontend (What will send in the starting parametres, are the customers because they will be the ones who see the food)
//		
//			The starting parametres should be sent in from the frontend, and read in from our waiters/API files.
//		The backend/kitchen should then start operation based on those parametres passed in from the Waiters/API
//		and begin simulation, saving its state to the Waiter/API Files.
//		Hopefully everything should be easy enough to figure out and apologies if not.
//
//
//
//		PLEASE send back feedback if you have any, I can be found at the following:
//			Email: 		cesar.hannin@hotmail.com
//			Instagram:	just.cesar.man
//			Reddit:		I_dont_like_pears
//			Discord:	Djagamoe #3385
//
//	Good hunting S.T.A.L.K.E.R						;)





int main(int argument_count,	const char** API_Folder_Path_argument) 
{
	Global_settings = Default_Parametres(); 	// These are our default values
							// Also gets our Log File pointer is up in read mode!

	if (Global_settings.Log_File_Ptr == NULL)	// Log file doesn't exist, need to make one
	{
		printf("\nCreating new Log file!");
		SLEEP(1);
		Global_settings.Log_File_Ptr = fopen(LOG_FILE, "a");
		print_logo(0, 'e', 'b'); 	// Print logo to both screen and log file
	}
	else	// The file does exist! We want to append to it though
	{
		printf("\nFile already exists...!");
		SLEEP(1);
		fclose(Global_settings.Log_File_Ptr);
		Global_settings.Log_File_Ptr = fopen(LOG_FILE, "a");
		print_logo(0, 'e', 's'); 	// Print logo to just the screen... forget the log file
	}
	
	NAP(200);
	
	//Step 1: Introductions!
	Log_To_File("\n\n#######################################################################################################################\n\n", false);
	Log_To_File("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -", false);
	Log_To_File("\t       |                    Backend ", false, false);
	Log_To_File( OAL_VERSION, false, false);
	Log_To_File(" Started! Wish us luck!                      |", false, true);
	Log_To_File("\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n", false);


	//Step 2: Check our Application Arguments!
	if (argument_count == 1) 	// No arguments given is 1, Giving an arguement is 2+... QUE???
		{	API_Folder_Path_argument[1] = DEFAULT_API_FOLDER_PATH;	}
	


	Global_settings.API_Folder_Path = API_Folder_Path_argument[1];


	Log_To_File("Using API Path of:\t┐");
	Log_To_File(API_Folder_Path_argument[1], false);


	// Step 2: What does our .ALC have to say?
	Get_Set_Global_Settings();

	// Step 3: Init our What.ToDo thread
	std::thread what_todo_thr(Check_ToDo_File);
	what_todo_thr.detach();

	//////////////////	DEBUGING CODE GOES HERE	//////////////////
	Testing:

	//print_logo(0, 'e', 's');





	printf("\nyay all done... Press enter to exit\n\n");

	//////////////////////////////////////////////////////////////

	getchar(); // Get an enter
	what_todo_thr.~thread();



	Log_To_File("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   BACKEND HAS ENDED   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", true);
	Log_To_File("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", false);

	return 0;
}
