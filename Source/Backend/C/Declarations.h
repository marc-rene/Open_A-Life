#include        		<stdio.h>
#include        		<stdlib.h>
#include				<string.h>

#pragma once



#ifdef _WIN32
	#include <Windows.h>
	#define AM_I_RUNNING_WINDOWS 1
	#define	DEFAULT_API_FOLDER_PATH "..\\..\\API" 

#else
	#include <unistd.h>
	#define AM_I_RUNNING_WINDOWS 0
	#define	DEFAULT_API_FOLDER_PATH	"../../API" 
#endif





typedef				unsigned __int8					bool;
#define				false							0
#define				true							1

typedef         	__int8         					mint;	//	micro int, or "mint"... I thought it was cute
typedef         	unsigned __int8					uMint;                    	                        
typedef         	unsigned short 					uShort;                       	
typedef				unsigned int					uInt;						



#define         	CONFIG_FILE       				"Settings.OALC"			//	Lets get all our details and parametres from here! ( OALC = Open A-Life Config )  
#define				STATUS_READ_FILE				"Status.stat"			// 	This should be read to determine if we should exit or not, should be determined by a 1 or 0
#define				WORLD_WRITE_FILE				"writing.world"
#define				WORLD_READ_FILE					"read.world"
#define				FILE_PATH_BUFFER_SIZE			4096



#define         	PRINT_LOW_SEVERITY_ERROR        printf("\nMinor Tomfoolery error")
#define         	PRINT_MED_SEVERITY_ERROR        printf("\nWell... Shit, Error")
#define         	PRINT_HIGH_SEVERITY_ERROR       printf("\nOH GOD HELP ME ERROR")



#define         	THIN_LINE                   	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - -");
#define         	THICK_LINE                  	printf("\n###################################################");



#define 			NAP(x)							Sleep(x * Global_settings.SPEED_DIVIDER)		// 	milliseconds
#define				SLEEP(x)						Sleep(x * Global_settings.SPEED_DIVIDER * 1000)	//	seconds


#define     		BORING_LOG(x)					if(Global_settings.LOG_LEVEL >= 3){	printf("\n"); printf(x);	}
#define     		INTERESTING_LOG(x)       		if(Global_settings.LOG_LEVEL >= 2){	printf("\n"); printf(x);	}
#define     		CRUCIAL_LOG(x)       			if(Global_settings.LOG_LEVEL >= 1){	printf("\n"); printf(x);	}



#define				IF_HIGH_PERFORMANCE				if(Global_settings.USE_HIGH_PERFORMANCE_MODE)	// 	My laptop may not be the fastest thing in the world...
#define				IF_LOW_PERFORMANCE				if(!Global_settings.USE_HIGH_PERFORMANCE_MODE)	//	in fact it's not fast at all actually...
																				
																

typedef enum	//	Faction Organisational Structures
{		
	Centrally_Planned 	= 	'C',		// 	Holds Land, Needs a Home/HQ			(Red Army, US Army)
	Antonomous			=	'A', 		// 	Holds Land, Doesn't need a Home/HQ	(Wildlife, Bandits)
	Traders				=	'T',		// 	Don't hold land, Enters into targeted Land secondary Slots 
	Disease_Like		=	'D'			// 	Don't hold land, Enters into adjacent Land Secondary Slots
}	
Faction_Structures;	



typedef enum	//	Climate Types
{ 
	Cold 	= 	'C',
	Mild 	= 	'M',
	Hot 	= 	'H'
}
Climates_Types; 	



typedef enum 	// 	Storm Types
{ 
	Blizzard				=	'B', 
	Terrential_Rain			=	'R', 
	Heatwave				=	'H', 
	PSY_Emmission			=	'P',
	Land_Alter_Emmission	=	'L'	 
}
Storms_Types; 



struct Faction_Settings
{
	short 						Agression_scale; 	// a scale from -100 to 100... it's a short instead of a mint to prevent over/under flowing... avoid a Gandhi situation ;D
	char* 						Faction_Name;
	char* 						Faction_Initials;
	uShort 						Faction_Home;
	uShort 						Starting_Strength;
	bool						Is_Essential;
	Faction_Structures			Structure;
};



typedef struct Parametres	// MAKE SURE THAT THERE'S ONLY THE ONE
{
	uMint  						HOW_MANY_FACTIONS;
	uMint   					LOG_LEVEL;
	uMint   					WORLD_WIDTH;
	uMint   					WORLD_HEIGHT;
	uMint						Random_Strength_Range_MAX;
	uMint						Random_Strength_Range_MIN;
	uMint						File_ReOpen_Attempts;
	bool						USE_HIGH_PERFORMANCE_MODE;
	uShort 						WORLD_SIZE;
	FILE*						World_Write_File_ptr;
	uShort						SPEED_DIVIDER;	// this is mostly for Speed control... a bigger number means the program will run slower but use up less resources hopefully
}	
Parametres;

struct Parametres Global_settings;



//	Function Declarations should go here:	- - - - - - - - - - - - - -
bool Check_file_is_open(FILE*, char*, const char*, int, bool);
void Init_Global_Settings();