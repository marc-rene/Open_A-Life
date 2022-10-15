#include	"Declarations.hpp"

#pragma once



//... Aight
//	Lets do this!!!
//	我们开始吧！！！
//	Make sure to read the documentation at https://github.com/marc-rene/Open_A-Life
//	for more a better explanation of what's going on! 



struct FACTION
{
	uShort 			ID;
	const char* 		Name;
	Faction_Types		Type;
	Endgame_Aims		Objective;

	FACTION();
	FACTION(uShort, const char*, Faction_Types, Endgame_Aims);

};


FACTION::FACTION(uShort id, const char* name, Faction_Types type, Endgame_Aims aim)
{
	ID 		= id;
	Name 		= name;
	Type 		= type;
	Objective 	= aim;
}