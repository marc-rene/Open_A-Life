#include        		<stdio.h>
#include        		<stdlib.h>
#include				<time.h>
#include				<string.h>
#include				<string>
#include				<iostream>
#include				<fstream>
#include 				<thread>



#pragma once



#ifdef _WIN32
	#include 	<Windows.h>
	#define 	AM_I_RUNNING_WINDOWS 1
	#define		DEFAULT_API_FOLDER_PATH "..\\..\\API" 

#else
	#include 	<unistd.h>
	#define 	AM_I_RUNNING_WINDOWS 0
	#define		DEFAULT_API_FOLDER_PATH	"../../API" 
	
#endif

#define		NEEDED_THREAD_COUNT	5	



typedef         	__int8         					mint;	//	micro int, or "mint"... I thought it was cute
typedef         	unsigned __int8					uMint;                    	                        
typedef         	unsigned short 					uShort;                       	
typedef				unsigned int					uInt;						



#define         	CONFIG_FILE       				"Settings.ALC"			//	Lets get all our details and parametres from here! ( OALC = Open A-Life Config )  
#define				STATUS_READ_FILE				"Status.stat"			// 	This should be read to determine if we should exit or not, should be determined by a 1 or 0
#define				WORLD_WRITE_FILE				"writing.world"
#define				WORLD_READ_FILE					"read.world"
#define				LOG_FILE						"What_Happened.log"
#define				FILE_PATH_BUFFER_SIZE			4096
#define				GENERIC_CHAR_BUFFER_SIZE		3072



#define         	LOW_SEVERITY_ERROR        "# [ERROR] Minor Tomfoolery error   #"
#define         	MED_SEVERITY_ERROR        "### [ERROR] Well... Shit, Error   ###"
#define         	HIGH_SEVERITY_ERROR       "##### [ERROR] OH GOD HELP ME ERROR   #####"



#define         	THIN_LINE                   	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - -");
#define         	THICK_LINE                  	printf("\n###################################################");



#define 			NAP(x)							Sleep(x * Global_settings.SPEED_DIVIDER)		// 	milliseconds
#define				SLEEP(x)						Sleep(x * Global_settings.SPEED_DIVIDER * 1000)	//	seconds


//#define     		BORING_LOG(x)					if(Global_settings.LOG_LEVEL >= 3){	printf("\n"); printf(x);	}





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



typedef enum
{
	SEVERE_ERROR 	= 1,
	MILD_ERROR		= 2,
	MINOR_ERROR		= 3,
	no_error		= 4
} Error_Types;



typedef enum
{
	IMPORTANT 	= 1,
	MILD_IMPORTANCE	= 2,
	BORING		= 3,
	no_importance	= 4
} Importance;



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
	uMint						File_ReOpen_Attempts;
	bool						USE_HIGH_PERFORMANCE_MODE;
	uShort 						WORLD_SIZE;
	FILE*						Log_File_Ptr;
	const char*					API_Folder_Path;
	uShort						SPEED_DIVIDER;	// this is mostly for Speed control... a bigger number means the program will run slower but use up less resources hopefully
}	
Parametres;

struct Parametres Global_settings;



//	Function Declarations should go here:	- - - - - - - - - - - - - -

void Log_To_File(const char*);
void Log_To_File(std::string);
void LOG(const char*, Importance, Error_Types, bool);
void LOG(const char*, Importance);
void LOG(const char*);
void LOG(std::string);
void LOG(std::string, Importance);
void LOG(const char*, Error_Types);
void LOG(std::string, Error_Types);
Parametres Default_Parametres();
bool Check_File_Is_Open(FILE*, const char*, const char*, int, bool);
bool Check_File_Exists(const char*, bool);
void Get_File_Path(const char*, const char*, char*);
void Check_Status_File();
void Log_To_File(const char*);
void Log_To_File(std::string);
int Get_Value_From_Settings(const char*);
