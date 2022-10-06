#include    	"Declarations.h"
#pragma once



//	The following comments are copy+pasted from the github : https://github.com/marc-rene/Open_A-Life
// the world is divided up into cells
struct  Cell
{
	FACTION_ID_MEMORY_TYPE	ID_of_Faction_Here;				// The integer ID of the owning faction
	
	// Weather/Physical
	mint			Base_Traversing_Difficulty; 	// how difficult the cell is to physically traverse
	mint			Traversing_difficulty_Modifier; // any modifiers we want to add
	Climates_Types	Climate;						// which climate is currently active
    Storms_Types	Weather;						// which weather is currently active 
	
	
	
	// Resources
	uShort 			Population_Size;
	mint			Population_Contentness;			// Should be a number between -100 ~ +100
	uShort			Munitions_Count;	
	uShort			Supplies_Count;

	uShort			Visitor_Capacity;				// How many spare slots for other factions are there
	struct	Cell_Visitor* 	All_Visitors;			// An array of Faction ID's in those slots and their buffs and debuffs there
};







struct Cell_Visitor
{
	FACTION_ID_MEMORY_TYPE		Visiting_Faction_ID;

	Cell_Resource 	Affects_Which_Resource;

	uMint			Competency;	// How good are they at their job?
	short 			Change_Amount_Over_Time;

	uInt Time_Spent_Here;  	/*	~681 years until an integer overflow occurs 
								assuming this increments every 5 seconds!*/
	uInt Leaves_After_X_Turns;
};



struct Co_Ordinates
{
	unsigned int X;
	unsigned int Y;
};



Co_Ordinates Int_To_Co_Ordinates(uInt Index)
{
	if (Index >= Global_settings.WORLD_SIZE)
	{
		LOG("Int to cordinates conversion function was given an invalid index to convert, maybe it's too big", MILD_ERROR);
		return Co_Ordinates {4294967290, 4294967290}; // if we EVER see 4294967290, tom foolery has occured
	}
	
	Co_Ordinates temp_co;
	temp_co.X = Index % Global_settings.WORLD_WIDTH;
	temp_co.Y = Global_settings.WORLD_HEIGHT - (Index / Global_settings.WORLD_WIDTH) -1;
	return temp_co;
}



uInt Co_Ordinates_to_Int(Co_Ordinates co_ords)
{
	if ( (co_ords.X == 4294967290) || (co_ords.Y == 4294967290) ) /////	HEY MAKE SURE THIS WORKS CAUSE I CHANGED IT
	{
		LOG("cordinates to int conversion function was given an invalid coordinate to convert", MILD_ERROR);
		return 4294967290;		
	}
	
	return (Global_settings.WORLD_WIDTH * (Global_settings.WORLD_HEIGHT - co_ords.Y - 1) ) + co_ords.X;
}