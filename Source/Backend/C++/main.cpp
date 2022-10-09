#include "File_IO.h"
#include "UTILITY_ITEMS.h"
#include "World.h"
#include "logo.h"



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
	//print_logo(2);

	Global_settings = Default_Parametres(); 		// 	These are our default values
	Global_settings.Log_File_Ptr = fopen(LOG_FILE, "a");	// 	Make sure our Log File pointer is up and running!
	goto Testing;	

	Log_To_File("#########################################################\n\n\n", false);
	Log_To_File("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -", false);
	Log_To_File("Backend Started! Wish us luck!");
	Log_To_File("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -", false);


	//	Check our Arguments!
	if (argument_count == 1) 	// No arguments given is 1, Giving an arguement is 2+... QUE???
		{	API_Folder_Path_argument[1] = DEFAULT_API_FOLDER_PATH;	}
	


	Global_settings.API_Folder_Path = API_Folder_Path_argument[1];


	Log_To_File("Using API Path of:\t┐");
	Log_To_File(API_Folder_Path_argument[1], false);


	// Step 1: What does our .ALC have to say?
	Get_Set_Global_Settings();



	//////////////////	DEBUGING CODE GOES HERE	//////////////////
	Testing:


	
	print_logo(0);
	SLEEP(2);
	print_logo(1);
	SLEEP(2);
	print_logo(2);
	SLEEP(2);
	print_logo(3);
	SLEEP(2);
	print_logo(4);
	SLEEP(2);





	printf("\nyay all done... Press enter to exit\n\n");

	//////////////////////////////////////////////////////////////

	getchar(); // Get an enter
	return 0;
}
