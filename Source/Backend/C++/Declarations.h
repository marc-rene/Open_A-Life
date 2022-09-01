#include        		<stdio.h>
#include        		<stdlib.h>
#include        		<iostream>
#include        		<vector>
#include        		<thread>
#include        		<string>
#include        		<fstream>
#include				<algorithm>


#define         	mint                        	__int8           	//	micro int, or "mint"... I thought it was cute
#define         	uMint                       	unsigned __int8                        
#define         	uShort                         	unsigned short 
#define				uInt							unsigned int

#define         	MINT_CONFIG_FILE_PATH       	"../../API/config.mints"
#define         	FAC_CONFIG_FILE_PATH       		"../../API/Faction.fucc"		// "factions-universelles cadres et comment on se citer"... Nothing else
#define				STATUS_READ_FILE_PATH			"../../API/Keep_Reading.bool"	// This should be read to determine if we should exit or not, determined by a 1 or 0
#define				NEW_REPORT_FILE_PATH			"../../API/News.report"			// This should be used to update the stage (GUI/Front-End) about any updates!
#define				WORLD_FILE_PATH					"../../API/map.world"
#define				WORLD_BACKUP					"../../API/backup.world"

#define         	PRINT_LOW_SEVERITY_ERROR         std::cout << "\nMinor Tomfoolery error"
#define         	PRINT_MED_SEVERITY_ERROR         std::cout << "\nWell... Shit, Error"
#define         	PRINT_HIGH_SEVERITY_ERROR        std::cout << "\nOH GOD HELP ME ERROR"

#define         	THIN_LINE                   	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -")
#define         	THICK_LINE                  	printf("\n###############################################################################################")

#define 			SLEEP(x)						std::this_thread::sleep_for(std::chrono::seconds(x * SPEED_DIVIDER) )
#define 			NAP(x)							std::this_thread::sleep_for(std::chrono::milliseconds(x * SPEED_DIVIDER) )

#define     		BORING_LOG(x)					if(LOG_LEVEL >= 3){std::cout << "\n" << x ;}
#define     		INTERESTING_LOG(x)       		if(LOG_LEVEL >= 2){std::cout << "\n" << x ;}
#define     		CRUCIAL_LOG(x)       			if(LOG_LEVEL >= 1){std::cout << "\n" << x ;}


unsigned int		SPEED_DIVIDER				=	1;		// this is mostly for Speed control... a bigger number means the program will run slower but use up less resources hopefully
bool				USE_HIGH_PERFORMANCE_MODE	=	false;
#define				IF_HIGH_PERFORMANCE				if(USE_HIGH_PERFORMANCE_MODE)	// 	My laptop may not be the fastest thing in the world...
#define				IF_LOW_PERFORMANCE				if(!USE_HIGH_PERFORMANCE_MODE)	//	in fact it's not fast at all actually...
																				
																

//	The military structure of a faction could be organised in 3 distinct ways...
//		1.	Disorganised: 	This would be your Bandits and Mercenaries... No central planning at all.
//
//		2.	Migrant:		This would be your Roma and wildlife, if we ever wanted to make them a faction...
//							these people move constantly to empty spots only
//
//		3.	Organised:		Normal Military as we've come to know them, has central planning 

enum	Faction_Structure		{	Disorganised,	Migrant,	Organised	};	



// 	They're up here to make them publicly accessable from now on
enum Climates 	{ Cold = 'C', 	Mild = 'M', 	Hot = 'H' 	}; 	
enum Storms 	{ Blizzard, Terrential_Rain, Heatwave, Emmission }; 
//	We'll be seeing this mostly in World.h



struct Faction_Settings
{
	std::string 		Faction_Name;
	std::string 		Faction_Initials;
	uShort 				Faction_Home;
	uShort 				Starting_Strength;
	bool				Is_Essential;
	Faction_Structure	Organisation_Structure;
};

std::vector<Faction_Settings> Faction_details;


/////// 	  Now we getting into some... Undefined stuff...		//////
uMint  										HOW_MANY_FACTIONS;			//
uMint   									LOG_LEVEL;					//
uMint   									WORLD_WIDTH;				//
uMint   									WORLD_HEIGHT;				//
uMint										Random_Strength_Range_MAX;	//
uMint										Random_Strength_Range_MIN;	//
uShort 										WORLD_SIZE;					//
//   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -  //

	