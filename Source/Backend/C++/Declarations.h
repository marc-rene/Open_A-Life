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



#define 	mint	       	__int8		//	micro int, or "mint"... I thought it was cute
#define 	uMint	       	unsigned __int8
#define 	uShort	       	unsigned short
#define		uInt			unsigned int
#define		chunky			int64_t 	//	Just to avoid that whole long == 4 bytes/8bytes confusion
#define		uChunky			unsigned int64_t
#define		FACTION_ID_MEMORY_TYPE	unsigned short	// This is incase we ever want 65000+ factions





#define         	CONFIG_FILE       				"Settings.ALC"			//	Lets get all our details and parametres from here! ( OALC = Open A-Life Config )  
#define				STATUS_READ_FILE				"What.todo"				// 	This should be read to determine our operation and what to do
#define				WORLD_WRITE_FILE				"World.w"
#define				WORLD_READ_FILE					"World.csv"
#define				LOG_FILE						"What_Happened.log"
#define				FILE_PATH_BUFFER_SIZE			4096
#define				GENERIC_CHAR_BUFFER_SIZE		3072



#define         	LOW_SEVERITY_ERROR        "  # [ERROR] Minor Tomfoolery error    		#"
#define         	MED_SEVERITY_ERROR        "# # # [ERROR] Well... Shit, Error    	# # #"
#define         	HIGH_SEVERITY_ERROR       "# # # # # [ERROR] OH GOD HELP ME ERROR   # # # # #"



#define 			NAP(x)							Sleep(x * Global_settings.SPEED_DIVIDER)		// 	milliseconds
#define				SLEEP(x)						Sleep(x * Global_settings.SPEED_DIVIDER * 1000)	//	seconds



#define				IF_HIGH_PERFORMANCE				if(Global_settings.USE_HIGH_PERFORMANCE_MODE)	// 	My laptop may not be the fastest thing in the world...
#define				IF_LOW_PERFORMANCE				if(!Global_settings.USE_HIGH_PERFORMANCE_MODE)	//	in fact it's not fast at all actually...
																				
																

typedef enum	//	Faction Organisational Structures
{		
	Centrally_Planned 	= 	'C',		// 	Holds Land, Needs a Home/HQ			(Red Army, US Army)
	Antonomous			=	'A', 		// 	Holds Land, Doesn't need a Home/HQ	(Wildlife, Bandits)
	Travellers			=	'T',		// 	Don't hold land, Enters into targeted Land secondary Slots 
	Disease_Like		=	'D'			// 	Don't hold land, Enters into adjacent Land Secondary Slots
}	
Faction_Types;	



typedef enum
{
	SEVERE_ERROR 	= 	1,
	MILD_ERROR		= 	2,
	MINOR_ERROR		= 	3,
	no_error		= 	4
} 
Error_Types;



typedef enum
{
	IMPORTANT 		= 	1,
	MILD_IMPORTANCE	= 	2,
	BORING			= 	3,
	no_importance	= 	4
} 
Importance;



// World Specific	-	-	-	-	-	-	-	-	-	-	-	-	-	-
typedef enum	//	Directions             	
{   
	North	=	'N',  
	East	=	'E',   
	West	=	'W',    
	South	=	'S'  
} 
Direction;



typedef enum	//	World Wrapping Setting              	
{   
	No_Wrap 			=	0,
	Horizontal_Wrap		=	1,
	Vertical_Wrap		=	2,
	Any_Wrap			=	3
} 
World_Wrap_Config;



typedef enum	//	What resources might a cell have
{	
	Population_Size			=		'P',	
	Population_Contentness	=		'C',	
	Munitions_Count			=		'M',	
	Supplies_Count			=		'S'	
} 
Cell_Resource;



typedef enum	//	Climate Types
{ 
	Tundra 	= 	'T',
	Cold 	= 	'C',
	mild 	= 	'm',
	Hot 	= 	'H',
	Desert	=	'D'
}
Climates_Types; 	



enum purpose_of_visit 
{
	Trade			=	't',
	Incite_Revolt	=	'r',	
	Beseige			=	'b',	// Should make difficulty to traverse way worse
	Attack			=	'a',
	Sabotage		= 	's'

};



typedef enum 	// 	Storm Types
{ 
	Blizzard				=	'B', 
	Terrential_Rain			=	'R', 
	Heatwave				=	'H', 
	Sandstorm				=	'S', 
	PSY_Emmission			=	'P',
	Land_Alter_Emmission	=	'L',	 
	no_storm				=	'n',	 
}
Storms_Types; 
//	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-



typedef struct Parametres	// MAKE SURE THAT THERE'S ONLY THE ONE
{
	uShort  					HOW_MANY_FACTIONS;
	uMint   					LOG_LEVEL;
	uShort   					WORLD_WIDTH;
	uShort   					WORLD_HEIGHT;
	uInt 						WORLD_SIZE;
	World_Wrap_Config			World_Wrap_Setting;
	uMint						File_ReOpen_Attempts;
	bool						USE_HIGH_PERFORMANCE_MODE;
	FILE*						Log_File_Ptr;
	const char*					API_Folder_Path;
	uMint						SPEED_DIVIDER;	// this is mostly for Speed control... a bigger number means the program will run slower but use up less resources hopefully
}	
Parametres;



struct 	Parametres 	Global_settings;
struct 			Tile;
struct 			Co_Ordinates;
struct 			Cell_Visitor;



//	Function Declarations should go here:	- - - - - - - - - - - - - -

void LOG(const char*, Importance, Error_Types, bool);
void LOG(std::string, Importance, Error_Types, bool);
void LOG(const char*, Importance);
void LOG(std::string, Importance);
void LOG(const char*);
void LOG(std::string);
void LOG(const char*, Error_Types);
void LOG(std::string, Error_Types);

Parametres Default_Parametres();

bool Check_File_Is_Open(FILE*, const char*, const char*, int, bool);
bool Check_File_Exists(const char*, bool);
void Get_File_Path(const char*, const char*, char*);
void Check_Status_File();
void Log_To_File(const char*, bool);
void Log_To_File(const char*);
void Log_To_File(std::string);
int Get_Value_From_Settings(const char*);
