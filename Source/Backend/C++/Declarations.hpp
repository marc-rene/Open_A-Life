#include	<stdio.h>
#include	<string>
#include	<fstream>
#include	<thread>

#pragma once



// Do we want to Have agents and the advanced features?
// Work in progress, keep this at 1 for now
//#define 	USE_ADVANCED 	1 	



#ifdef _WIN32
	#include	<Windows.h>
	#define		AM_I_RUNNING_WINDOWS 		1
	#define		DEFAULT_API_FOLDER_PATH		"..\\..\\API" 

#else
	#include	<unistd.h>
	#define 	AM_I_RUNNING_WINDOWS 		0
	#define		DEFAULT_API_FOLDER_PATH		"../../API" 
	
#endif



#define		NEED_X_THREADS	2 	// How many threads will we need?	
					//	Thread 0 - Faction & Agent thread
					//	Thread 1 - What.ToDo check

//	Define our data types!
#define		mint		__int8			//	micro int, or "mint"... I thought it was cute
#define		uMint		unsigned __int8
#define		uShort		unsigned short
#define		uInt		unsigned int
#define		chunky		int64_t 		//	Just to avoid that whole long == 4 bytes/8bytes confusion
#define		uChunky		uint64_t




#define         CONFIG_FILE       		"Settings.ALC"		//	Lets get all our details and parametres from here! ( OALC = Open A-Life Config )  
#define		WHAT_TODO_FILE			"What.todo"		// 	This should be read to determine our operation and what to do
#define		WORLD_WRITE_FILE		"World.w"
#define		WORLD_READ_FILE			"World.csv"
#define		FACTIONS_FILE			"Factions.csv"
#define		AGENTS_FILE			"Agents.csv"
#define		LOG_FILE			"What_Happened.log"
#define		FILE_PATH_BUFFER_SIZE		4096
#define		GENERIC_CHAR_BUFFER_SIZE	3072
#define		OAL_VERSION			"Ver.0.1.1b"

#define		CO_ORDINATE_ERROR_NUMBER	4294967290				



#define 	LOW_SEVERITY_ERROR  	"  # [ERROR] Minor Tomfoolery error	#"
#define 	MED_SEVERITY_ERROR  	"# # # [ERROR] Well... Shit, Error    	# # #"
#define 	HIGH_SEVERITY_ERROR 	"# # # # # [ERROR] OH GOD HELP ME ERROR # # # # #"



#define 	NAP(x)			Sleep(x * Global_settings.SPEED_DIVIDER)		//	milliseconds
#define		SLEEP(x)		Sleep(x * Global_settings.SPEED_DIVIDER * 1000)		//	seconds

#define		THREAD_CHECK		if(Global_settings.Permission_to_run == true){	
#define		THREAD_CHECK_FAIL	if(Global_settings.Permission_to_run == false){

#define		IF_HIGH_PERFORMANCE	if(Global_settings.USE_HIGH_PERFORMANCE_MODE)		// 	My laptop may not be the fastest thing in the world...
#define		IF_LOW_PERFORMANCE	if(!Global_settings.USE_HIGH_PERFORMANCE_MODE)		//	in fact it's not fast at all actually...
																				
																

// Faction Specific	~  ~  ~  ~  ~  ~  ~  ~  ~  ~	~  ~  ~  ~  ~  ~  ~  ~  ~  ~
typedef enum	Faction_Types		//	Faction Organisational Structures
{		
	Centrally_Planned 	=	'C',		// 	Holds Land, Needs a Home/HQ		(Red Army, US Army)
	Autonomous		=	'A', 		// 	Holds Land, Doesn't need a Home/HQ	(Wildlife, Bandits)
	Travellers		=	'T',		// 	Don't hold land, Enters into targeted Land secondary Slots via agents (traders, disease, etc) 
}	
Faction_Types;	


typedef enum	Endgame_Aims
{
	Self_Sufficiency	=	'S',		//	Iceland, wants to not need anyone else ideally
	Total_Domination	=	'D',		//	Russia,	wants to conquour all
	Trade_Power		=	'T',		//	Ireland, "...did someone say... TRADE DEAL???"
	Absolute_Power		=	'P',		//	U.S.A, Wants to be the strongest
	Defensive		=	'D',		//	Ukraine, Wants to defend its borders first, trade and peace second
	Total_War		=	'W',		//	https://www.youtube.com/watch?v=jt_9fsA_XmA | https:// www.meme-arsenal.com/memes/e4ea924a091639066da3b82277aded97.jpg
							//	 ^-> Does War cause it's fun
	Dont_Care		=	'C',		// 	They just chilling... no aims or wishes, ideal for wildlife
	Revenge			=	'R'		// 	They just chilling... until theres a need for revenge
}
Endgame_Aims;
// ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~



// File-IO Specific	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#
typedef enum
{
	SEVERE_ERROR		= 	1,
	MILD_ERROR		= 	2,
	MINOR_ERROR		= 	3,
	no_error		= 	4
} 
Error_Types;


typedef enum
{
	IMPORTANT		= 	1,
	MILD_IMPORTANCE		= 	2,
	BORING			= 	3,
	no_importance		= 	4
} 
Importance;
// 	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#



// World Specific	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
typedef enum	Direction             	
{   
	North		=	'N',  
	East		=	'E',   
	West		=	'W',    
	South		=	'S'  
} 
Direction;


typedef enum	World_Wrap_Config             	
{   
	No_Wrap 		=	0,
	Horizontal_Wrap		=	1,
	Vertical_Wrap		=	2,
	Any_Wrap		=	3
} 
World_Wrap_Config;


typedef enum	Cell_Resource		//	What resources might a cell have
{	
	Population_Size			=	'P',	
	Population_Contentness		=	'C',	
	Munitions_Count			=	'M',	
	Supplies_Count			=	'S'	
}
Cell_Resource;


typedef enum	Climates_Types 
{ 
	Tundra 		= 	'T',
	Cold 		= 	'C',
	Mild 		= 	'm',
	Hot 		= 	'H',
	Desert		=	'D'
}
Climates_Types; 	


typedef enum 	purpose_of_visit  
{
	Trade			=	't',
	Incite_Revolt		=	'r',	
	Beseige			=	'b',	// Should make difficulty to traverse way worse
	Attack			=	'a',
	Defend			=	'd',
	Sabotage		= 	's',
	Visiting		=	'v',
	Passing_By		=	'p'	// They're moving to another cell
}
purpose_of_visit;


typedef enum 	Storms_Types
{ 
	Blizzard		=	'B', 
	Terrential_Rain		=	'R', 
	Heatwave		=	'H', 
	Sandstorm		=	'S', 
	PSY_Emmission		=	'P',
	Land_Alter_Emmission	=	'L',	 
	no_storm		=	'n',	 
}
Storms_Types; 
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*



typedef struct Parametres	// MAKE SURE THAT THERE'S ONLY THE ONE
{
	uShort  			HOW_MANY_FACTIONS_START;
	uShort  			MAX_NUMBER_OF_FACTIONS;
	uShort  			HOW_MANY_AGENTS_START;
	uShort  			MAX_NUMBER_OF_AGENTS;
	uMint   			LOG_LEVEL;
	uShort   			WORLD_WIDTH;
	uShort   			WORLD_HEIGHT;
	uInt 				WORLD_SIZE;
	World_Wrap_Config		World_Wrap_Setting;
	uMint				File_ReOpen_Attempts;
	bool				USE_HIGH_PERFORMANCE_MODE;
	FILE*				Log_File_Ptr;
	FILE*				What_Todo_Ptr;
	bool				Config_file_is_open;
	const char*			API_Folder_Path;
	uMint				SPEED_DIVIDER;		//	this is mostly for Speed control... a bigger number means the program will run slower but use up less resources... hopefully
	uShort				Unix_Time_Read_Leeway;	//	When reading unix time to determine if we should close or not, how many seconds leeway will we give until we NEED to close?
	std::ifstream			Config_File;
	bool				Permission_to_run = true;
}	
Parametres;



struct 	Parametres 	Global_settings;
struct 		Tile;
struct 		Co_Ordinates;
struct 		Cell_Visitor;



//	Function Declarations should go here:	- - - - - - - - - - - - - -
//	-	-	-	-	File IO.h	-	-	-	-	//

void LOG(const char*, Importance, Error_Types, bool);
void LOG(const char*, Importance);
void LOG(const char*, Error_Types);
void LOG(const char*);

void LOG(std::string, Importance, Error_Types, bool);
void LOG(std::string, Importance);
void LOG(std::string, Error_Types);
void LOG(std::string);

Parametres Default_Parametres();

bool Check_File_Is_Open(FILE*, const char*, const char*, int, bool);
bool Check_File_Exists(const char*, bool);
void Get_File_Path(const char*, const char*, char*);
void Check_Status_File();
void Log_To_File(const char*, bool, bool);
void Log_To_File(const char*, bool);
void Log_To_File(const char*);
void Log_To_File(std::string);
int Get_Value_From_Settings(const char*);

//	-	-	-	End of File IO.h Functions	-	-	-	//



//	-	-	-	-	 World.h 	-	-	-	-	//

Co_Ordinates Int_To_Co_Ordinates(uInt);


uInt Co_Ordinates_to_Int(Co_Ordinates);

//	-	-	-	End of World.h Functions	-	-	-	//



//	-	-	-	-	 Logo.h 	-	-	-	-	//

void print_logo(uMint, int, char);
void print_logo(uMint, char);
void print_logo(uMint, int);
void print_logo(uMint, char, char);

//	-	-	-	End of logo.h Functions	-	-	-	//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -